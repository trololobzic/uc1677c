#pragma once
#include <stdint.h>

namespace uc1677c
{

template<typename T, T v> struct integral_constant
{
    static const T value = v;
};

typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;

template<typename TI2C>
class has_bus_interface
{
    template<typename TBusIface>
    static auto test(int) -> decltype(
        (void)TBusIface::start_transmission(0),
        TBusIface::end_transmission(),
        (void)TBusIface::write_byte(0),
        (void)TBusIface::read_byte(),
        true_type()
    );

    template<typename>
    static false_type test(...);

public:
    static constexpr bool value = decltype(test<TI2C>(0))::value;
};

template<bool B, typename T = void>
struct enable_if {};

template<typename T>
struct enable_if<true, T> { typedef T type; };

template<typename T> struct is_integral       : false_type{};
template<> struct is_integral<bool>           : true_type{};
template<> struct is_integral<int8_t>         : true_type{};
template<> struct is_integral<uint8_t>        : true_type{};
template<> struct is_integral<int16_t>        : true_type{};
template<> struct is_integral<uint16_t>       : true_type{};
template<> struct is_integral<int32_t>        : true_type{};
template<> struct is_integral<uint32_t>       : true_type{};
template<> struct is_integral<int64_t>        : true_type{};
template<> struct is_integral<uint64_t>       : true_type{};

template<typename T> struct is_floating_point : false_type{};
template<> struct is_floating_point<float>    : true_type{};
template<> struct is_floating_point<double>   : true_type{};

template <typename F>
class ScopeGuard
{
public:
    explicit ScopeGuard(F && func) :
        _func(static_cast<F&&>(func)), _active(true)
    {}

    ~ScopeGuard()
    {
        if (_active)
        {
            _func();
        }
    }

    ScopeGuard(const ScopeGuard &) = delete;
    ScopeGuard& operator=(const ScopeGuard &) = delete;

    void dismiss()
    {
        _active = false;
    }

private:
    F _func;
    bool _active;
};

template<typename T>
struct ArrayWrapper
{
    ArrayWrapper(const T * data, uint16_t size) :
        data(data),
        size(size)
    {}
    const T * data = nullptr;
    uint16_t size = 0;
};

struct Utils
{
    static constexpr uint16_t number_of_bytes(uint16_t bits)
    {
        return bits / 8 + (bits % 8 ? 1 : 0);
    }

    template<typename T>
    static uint8_t absolute_value(T & value)
    {
        if (value < static_cast<T>(0))
        {
            value = -value;
            return '-';
        }
        return ' ';
    }

    static int32_t power_of_10(int32_t value)
    {
        if (value == 0)
        {
            return 1;
        }

        int return_value = 10;
        if (value > 1)
        {
            return_value *= power_of_10(value - 1);
        }
        return return_value;
    }
};

template<typename TI2C, uint16_t ram_size>
class Uc1677cBase
{
    static_assert(has_bus_interface<TI2C>::value,
        "\n\n[ERROR] The provided class does not match the required HAL interface!\n"
        "Expected: start_transmission(u8), end_transmission(), write_byte(u8)->bool, read_byte()->u8.\n");

    using I2C = TI2C;

public:
    Uc1677cBase() = default;

    bool init(bool battery_powered = true) const
    {
        const uint8_t bump = battery_powered ? 0xbf : 0xb0;

        if (!_set_cmd(0x12)) { return false; } //init
        if (!_set_cmd(0xFE)) { return false; }
        if (!_set_cmd(0xE0)) { return false; } //Device-Select
        if (!_set_cmd(bump)) { return false; } //charge bump ctrl
        if (!_set_cmd(0xAA)) { return false; }
        if (!_set_cmd(0xD4)) { return false; } //CLOCK OUT CTRL
        if (!_set_cmd(0xC0)) { return false; } //mode set
        if (!_set_cmd(0x11)) { return false; } //Frame-Rate ctrl
        if (!_set_cmd(0x35)) { return false; } //200Hz
        if (!_set_cmd(0x14)) { return false; }
        if (!_set_cmd(0xCE)) { return false; }
        if (!_set_cmd(0x1C)) { return false; } //read byte type
        if (!_set_cmd(0x51)) { return false; } //temperature ctrl

        return true;
    }

    uint8_t read_temperature() const
    {
        I2C::start_transmittion();
        I2C::write_byte(_addr | 0x01);
        auto retVal = I2C::read_byte();
        I2C::end_transmission();
        return retVal;
    }

    bool set_segment(uint16_t segment, bool value)
    {
        if (segment > (ram_size * 8 - 1) )
        {
            return false;
        }

        const uint8_t ram_byte_idx = segment / 8;
        const uint8_t byte_value = 0x80 >> (segment % 8);

        _ram[ram_byte_idx] &= ~byte_value;
        if (value)
        {
            _ram[ram_byte_idx] |= byte_value;
        }
        return true;
    }

    void clear_all()
    {
        for (uint16_t i = 0; i < ram_size; i++)
        {
            _ram[i] = 0;
        }
    }

    /// @brief Push RAM to UC1677C
    bool update() const
    {
        if (!_set_cmd(0x02)) { return false; } //Load-Data-Pointer
        if (!_set_cmd(0x48)) { return false; }//Load-Data-Pointer

        for (uint16_t i = 0; i < ram_size; i++)
        {
            if (!_set_data(_ram[i])) { return false; }
        }
        return true;
    }

    /// @brief Light or turn off all segments whithout changing RAM-memory
    bool light_all_segments(bool enable) const
    {
        uint8_t cmd = 0x14;
        if ( enable )
        {
            cmd |= 0x02;
        }

        return _set_cmd(cmd);
    }

    /// @brief Enable or disable display segments blinking
    /// @param freq Frequency of blinking [0...3]
    bool blink(uint8_t freq) const
    {
        if (freq > 3)
        {
            return false;
        }

        return _set_cmd(0xf0 | freq);
    }

protected:
    constexpr static uint8_t _addr = 0x70;
    uint8_t _ram[ram_size] = {0};

    static bool _set_cmd(uint8_t cmd)
    {
        ScopeGuard<void(*)()> guard(I2C::end_transmission);

        if (!I2C::start_transmission(_addr)) { return false; }
        if (!I2C::write_byte(0x00) ) { return false; }
        if (!I2C::write_byte(cmd) ) { return false; }

        return true;
    }

    static bool _set_data(uint8_t data)
    {
        ScopeGuard<void(*)()> guard(I2C::end_transmission);

        if (!I2C::start_transmission(_addr)) { return false; }
        if (!I2C::write_byte(0x40) ) { return false; }
        if (!I2C::write_byte(data) ) { return false; }

        return true;
    }
};

template<typename TController, typename TLcd>
class DeviceDisplayBase : public TController
{
public:
    enum class CharacterStrings
    {
        main,
        additional1,
        additional2,
        tariff
    };

    uint16_t blank = 0;
    enum Units : uint16_t
    {
        cos = 0x0001,
        percent = 0x0002,
        hz = 0x0004,
        watt = 0x0340,
        var = 0x06C0,
        kilo = 0x0020,
        giga = 0x0010,
        mega = 0x0008,
        hour = 0x0800,
        volt = 0x0040,
        amper = 0x0280,
    };

    enum Period : uint16_t
    {
        begin = 0x0001,
        last = 0x0002,
        total = 0x0004,
        year = 0x0008,
        month = 0x0010,
        day = 0x0020,
        winter = 0x0040,
        summer = 0x0080,
    };

    enum Phase : uint16_t
    {
        phase_word = 0x0001,
        phase_1 = 0x0002,
        phase_2 = 0x0004,
        phase_3 = 0x0008,
    };

    enum Tick : uint16_t
    {
        tick_1 = 0x0001,
        tick_2 = 0x0002,
        tick_3 = 0x0004,
        tick_4 = 0x0008,
        tick_5 = 0x0010,
        tick_6 = 0x0020,
        tick_7 = 0x0040,
        tick_8 = 0x0080,
    };

    enum Other : uint16_t
    {
        tariff_word = 0x0001,
        max_word = 0x0002,
        low_battery = 0x0004,
        reley = 0x0018,
        time = 0x0020,
        date = 0x0040,
    };

    void clear_string(CharacterStrings where)
    {
        const auto string_length = TLcd::_get_string_segments_map(where).size;
        for (uint16_t i = 0; i < string_length; i++)
        {
            _set_char_in_string(where, 0, i);
        }
    }

    template<typename T, typename enable_if<is_floating_point<T>::value, bool>::type = true>
    void print(CharacterStrings where, T value, uint16_t precision = 2)
    {
        clear_string(where);
        int16_t pos = TLcd::_get_string_segments_map(where).size - 1;
        const auto sign = Utils::absolute_value(value);
        const int32_t ten_to_precision_power = Utils::power_of_10(precision);

        int32_t int_part = static_cast<int32_t>(value);
        int32_t frac_part = static_cast<int32_t>((value - static_cast<T>(int_part)) * ten_to_precision_power);

        //try to eliminate potential rounding error
        if (frac_part >= ten_to_precision_power)
        {
            int_part += 1;
            frac_part = 0;
        }

        for(int i = 0 ; i < precision && pos >= 0; i++)
        {
            _set_char_in_string(where, _get_character(frac_part % 10 + '0'), pos--);
            frac_part /= 10;
        }

        uint8_t dot = _dot;
        if (!int_part)
        {
            _set_char_in_string(where, _get_character('0') | dot, pos--);
        }
        else while (int_part > 0 && pos >= 0)
        {
            _set_char_in_string(where, _get_character(int_part % 10 + '0') | dot, pos--);
            int_part /= 10;
            dot = 0;
        }

        if (pos >= 0)
        {
            _set_char_in_string(where, _get_character(sign), pos);
        }
    }

    template<typename T, typename enable_if<is_integral<T>::value, bool>::type = true>
    void print(CharacterStrings where, T value)
    {
        clear_string(where);
        int16_t pos = TLcd::_get_string_segments_map(where).size - 1;
        const auto sign = Utils::absolute_value(value);

        while (value > 0 && pos >= 0)
        {
            _set_char_in_string(where, _get_character(value % 10 + '0'), pos--);
            value /= 10;
        }

        if (pos >= 0)
        {
            _set_char_in_string(where, _get_character(sign), pos);
        }
    }

    void print(CharacterStrings where, const char * str)
    {
        uint16_t i = 0, pos = 0;
        bool skip_next_char;
        uint8_t character;

        while (str[i] != 0x00)
        {
            skip_next_char = false;
            character = _get_character(str[i]);

            if (str[i+1] == '.' || str[i+1] == ',')
            {
                character |= _dot ;
                skip_next_char = true ;
            }
            _set_char_in_string(where, character, pos++);

            i += skip_next_char ? 2 : 1 ;
        }
    }

    void set_unit(uint16_t unit_mask)
    {
        _set_segments_by_mask(TLcd::_get_unit_segments_map(), unit_mask);
    }

    void set_phase(uint16_t phase_mask)
    {
        _set_segments_by_mask(TLcd::_get_phase_segments_map(), phase_mask);
    }

    void set_period(uint16_t period_mask)
    {
        _set_segments_by_mask(TLcd::_get_period_segments_map(), period_mask);
    }

    void set_tick(uint16_t tick_mask)
    {
        _set_segments_by_mask(TLcd::_get_tick_segments_map(), tick_mask);
    }

    void set_other(uint16_t other_mask)
    {
        _set_segments_by_mask(TLcd::_get_other_segments_map(), other_mask);
    }

protected:

    struct Digit
    {
        uint8_t segment_a;
        uint8_t segment_b;
        uint8_t segment_c;
        uint8_t segment_d;
        uint8_t segment_e;
        uint8_t segment_f;
        uint8_t segment_g;
        uint8_t dot;
    };

    enum class UnitSegments{cos, percent, hz, m, g, k, w, a, t, hyphen, r, h, size};
    enum class PhaseSegments{phase_word, phase_1, phase_2, phase_3, size};
    enum class PeriodSegments{begin, last, total, year, month, day, winter, summer, size};
    enum class TickSegments{tick_1, tick_2, tick_3, tick_4, tick_5, tick_6, tick_7, tick_8, size};
    enum class OtherSegments{tariff_word, max_word, low_battery, reley_first_half, reley_second_half, time, date, size};

    static constexpr uint8_t _dot = 0x80;

    /// @brief Representation of each of the 256 ascii characters as 7 segments
    /// @verbatim
    ///  ---     A
    /// |   |  F   B
    ///  ---     G
    /// |   |  E   C
    ///  ---     D
    /// @endverbatim
    static uint8_t _get_character(uint8_t ascii_index)
    {
        static constexpr uint8_t alphabet[256] =
        {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x22, 0x36, 0x00, 0x00, 0x00, 0x02, // space ! " # $ % & '
            0x39, 0x0F, 0x00, 0x00, 0x00, 0x40, 0x00, 0x30, // ( ) * + , - . /
            0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, // 0 1 2 3 4 5 6 7
            0x7F, 0x6F, 0x09, 0x09, 0x00, 0x48, 0x00, 0x53, // 8 9 : ; < = > ?
            0x00, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x3D, // @ A B C D E F G
            0x76, 0x06, 0x0E, 0x75, 0x38, 0x55, 0x54, 0x3F, // H I J K L M N O
            0x73, 0x67, 0x50, 0x6D, 0x78, 0x1C, 0x3E, 0x6A, // P Q R S T U V W
            0x76, 0x72, 0x5B, 0x39, 0x30, 0x0F, 0x01, 0x08, // X Y Z [ / ] ^ _
            0x02, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x3D, // ` a b c d e f g
            0x76, 0x06, 0x0E, 0x75, 0x38, 0x55, 0x54, 0x3F, // h i j k l m n o
            0x73, 0x67, 0x50, 0x6D, 0x78, 0x1C, 0x3E, 0x6A, // p q r s t u v w
            0x76, 0x72, 0x5B, 0x39, 0x30, 0x0F, 0x01, 0x00  // x y z { | } ~ DEL
        };
        return alphabet[ascii_index];
    }

    void _set_char_in_string(CharacterStrings where, uint8_t character, uint8_t pos)
    {
        const auto segments_map = TLcd::_get_string_segments_map(where);
        if (pos > (static_cast<int16_t>(segments_map.size) - 1))
        {
		    return;
        }

        this->set_segment(segments_map.data[pos].segment_a, character & 0x01);
        this->set_segment(segments_map.data[pos].segment_b, character & 0x02);
        this->set_segment(segments_map.data[pos].segment_c, character & 0x04);
        this->set_segment(segments_map.data[pos].segment_d, character & 0x08);
        this->set_segment(segments_map.data[pos].segment_e, character & 0x10);
        this->set_segment(segments_map.data[pos].segment_f, character & 0x20);
        this->set_segment(segments_map.data[pos].segment_g, character & 0x40);
        this->set_segment(segments_map.data[pos].dot, character & 0x80);
    }

private:
    void _set_segments_by_mask(const ArrayWrapper<uint8_t> & segments, uint16_t mask)
    {
        if (!segments.data || !segments.size)
        {
            return;
        }

        for (uint16_t i = 0; i < segments.size ; i++)
        {
            this->template set_segment(segments.data[i], mask & (1 << i));
        }
    }
};

}
