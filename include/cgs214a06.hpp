#pragma once

#include "uc1677c.hpp"

namespace uc1677c
{

struct Cgs214a06Base
{

/// @brief List of raw segments. The order is defined in the datasheet.
enum Segments : uint8_t
{
     _8B,  _8C,  _8A,  _8G,  _8F,  _8E,  _P6,  _7D,  _7B,  _7C,  _7A,  _7G,  _7F,  _7E,  _P5,  _6D,
     _6B,  _6C,  _6A,  _6G,  _6F,  _6E,  _S2,  _S3,  _P4,  _5D,  _5B,  _5C,  _5A,  _5G,  _5F,  _5E,
     _P3,  _4D,  _4B,  _4C,  _4A,  _4G,  _4F,  _4E,  _P2,  _3D,  _3B,  _3C,  _3A,  _3G,  _3F,  _3E,
     _T1,  _S1,  _P1,  _2D,  _2B,  _2C,  _2A,  _2G,  _2F,  _2E,  _1B,  _1C,  _1A,  _1G,  _1F,  _1E,
     _T2,  _1D, _16E, _16F, _16D, _16G, _16C, _16B, _17E, _17F, _17D, _17G, _17C, _17B, _17A, _16A,
     _T3,  _T4, _18E, _18F, _18D, _18G, _18C, _18B, _P11, _18A, _19E, _19F, _19D, _19G, _19C, _19B,
    _P12, _19A,  _T5,  _T6, _20E, _20F, _20D, _20G, _20C, _20B, _P13, _20A, _21E, _21F, _21D, _21G,
    _21C, _21B, _P14, _21A, _22E, _22F, _22D, _22G, _22C, _22B, _P15, _22A,  _T7,  _T8, _23E, _23F,
    _23D, _23G, _23C, _23B, _P16, _23A,  _M1,  _T9,  _M2, _T10,  _M3, _T14,  _M4,  _S8,  _M7, _T15,
     _M5,  _S9,  _M6, _NO1,  _M8, _T16,  _M9, _S10, _15B, _15C, _15A, _15G, _15F, _15E, _15D, _NO2,
    _14B, _14C, _14A, _14G, _14F, _14E, _P10, _14D, _13B, _13C, _13A, _13G, _13F, _13E, _13D, _NO3,
     _S7, _T13, _12B, _12C, _12A, _12G, _12F, _12E,  _P9, _12D, _11B, _11C, _11A, _11G, _11F, _11E,
    _10D, _11D, _10B, _10C, _10A, _10G, _10F, _10E, _T12, _S6,    _3,   _2, _T11,   _1,  _P8,  _9D,
     _9B,  _9C,  _9A,  _9G,  _9F,  _9E,  _P7,  _8D,  _S5, _S4,

    size
};

static constexpr uint16_t ram_size = Utils::number_of_bytes(Segments::size);
};


template<typename TI2C>
class Cgs214a06 : public DeviceDisplayBase<Uc1677cBase<TI2C, Cgs214a06Base::ram_size>, Cgs214a06<TI2C>>, public Cgs214a06Base
{
public:
    using Base = DeviceDisplayBase<Uc1677cBase<TI2C, Cgs214a06Base::ram_size>, Cgs214a06<TI2C>>;
    using Digit = typename Base::Digit;
    using CharacterStrings = typename Base::CharacterStrings;

    friend Base;

protected:
    constexpr static uint8_t NO = 0xFF;

    static ArrayWrapper<Digit> _get_string_segments_map(CharacterStrings where)
    {
        switch(where)
        {
            case CharacterStrings::main:
            {
                static constexpr uint16_t _main_string_length = 8;
                static constexpr Digit _main_string_segments_map[_main_string_length] =
                {
                    {_16A, _16B, _16C, _16D, _16E, _16F, _16G,   NO},
                    {_17A, _17B, _17C, _17D, _17E, _17F, _17G,   NO},
                    {_18A, _18B, _18C, _18D, _18E, _18F, _18G, _P11},
                    {_19A, _19B, _19C, _19D, _19E, _19F, _19G, _P12},
                    {_20A, _20B, _20C, _20D, _20E, _20F, _20G, _P13},
                    {_21A, _21B, _21C, _21D, _21E, _21F, _21G, _P14},
                    {_22A, _22B, _22C, _22D, _22E, _22F, _22G, _P15},
                    {_23A, _23B, _23C, _23D, _23E, _23F, _23G, _P16}
                };

                return {_main_string_segments_map, _main_string_length};
            }

            case CharacterStrings::additional1:
            {
                static constexpr uint16_t _additional_string_1_length = 8;
                static constexpr Digit _additional_string_1_segments_map[_additional_string_1_length] =
                {
                    { _2A,  _2B,  _2C,  _2D,  _2E,  _2F,  _2G,  _P1},
                    { _3A,  _3B,  _3C,  _3D,  _3E,  _3F,  _3G,  _P2},
                    { _4A,  _4B,  _4C,  _4D,  _4E,  _4F,  _4G,  _P3},
                    { _5A,  _5B,  _5C,  _5D,  _5E,  _5F,  _5G,  _P4},
                    { _6A,  _6B,  _6C,  _6D,  _6E,  _6F,  _6G,  _P5},
                    { _7A,  _7B,  _7C,  _7D,  _7E,  _7F,  _7G,  _P6},
                    { _8A,  _8B,  _8C,  _8D,  _8E,  _8F,  _8G,  _P7},
                    { _9A,  _9B,  _9C,  _9D,  _9E,  _9F,  _9G,  _P8}
                };

                return {_additional_string_1_segments_map, _additional_string_1_length};
            }

            case CharacterStrings::additional2:
            {
                static constexpr uint16_t _additional_string_2_length = 6;
                static constexpr Digit _additional_string_2_segments_map[_additional_string_2_length] =
                {
                    {_10A, _10B, _10C, _10D, _10E, _10F, _10G,   NO},
                    {_11A, _11B, _11C, _11D, _11E, _11F, _11G,  _P9},
                    {_12A, _12B, _12C, _12D, _12E, _12F, _12G,   NO},
                    {_13A, _13B, _13C, _13D, _13E, _13F, _13G, _P10},
                    {_14A, _14B, _14C, _14D, _14E, _14F, _14G,   NO},
                    {_15A, _15B, _15C, _15D, _15E, _15F, _15G,   NO}
                };

                return {_additional_string_2_segments_map, _additional_string_2_length};
            }

            case CharacterStrings::tariff:
            {
                static constexpr uint16_t _tariff_string_length = 1;
                static constexpr Digit _tariff_string_segments_map[_tariff_string_length] =
                {
                    { _1A,  _1B,  _1C,  _1D,  _1E,  _1F,  _1G,  NO}
                };
                return {_tariff_string_segments_map, _tariff_string_length};
            }

            default:
                return {nullptr, 0};
        }
    }


    /// @brief Listing of units segments
    /// @details The segments are listed in the same order as in the Base::UnitSegments
    static ArrayWrapper<uint8_t> _get_unit_segments_map()
    {
        static constexpr uint8_t _unit_segments[static_cast<uint16_t>(Base::UnitSegments::size)] =
        {
            _T14, ///< cos
            _T15, ///< percent
            _T16, ///< hz
            _M1,  ///< m
            _M2,  ///< g
            _M3,  ///< k
            _M4,  ///< w
            _M5,  ///< a
            _M7,  ///< t
            _M6,  ///< -
            _M8,  ///< r
            _M9   ///< h
        };

        return {_unit_segments, static_cast<uint16_t>(Base::UnitSegments::size)};
    }


    /// @brief Listing of phase segments
    /// @details The segments are listed in the same order as in the Base::PhaseSegments
    static ArrayWrapper<uint8_t> _get_phase_segments_map()
    {
        static constexpr uint8_t _phase_segments[static_cast<uint16_t>(Base::PhaseSegments::size)] =
        {
            _T11, ///< phase_word
            _1,   ///< phase_1
            _2,   ///< phase_2
            _3    ///< phase_3
        };

        return {_phase_segments, static_cast<uint16_t>(Base::PhaseSegments::size)};
    }


    /// @brief Listing of period segments
    /// @details The segments are listed in the same order as in the Base::PeriodSegments
    static ArrayWrapper<uint8_t> _get_period_segments_map()
    {
        static constexpr uint8_t _period_segments[static_cast<uint16_t>(Base::PeriodSegments::size)] =
        {
            _T4, ///< begin
            _T5, ///< last
            _T3, ///< total
            _T6, ///< year
            _T7, ///< month
            _T8, ///< day
            _T9, ///< winter
            _T10 ///< summer
        };

        return {_period_segments, static_cast<uint16_t>(Base::PeriodSegments::size)};
    }


    /// @brief Listing of tick segments
    /// @details The segments are listed in the same order as in the Base::TickSegments
    static ArrayWrapper<uint8_t> _get_tick_segments_map()
    {
        static constexpr uint8_t _tick_segments[static_cast<uint16_t>(Base::TickSegments::size)] =
        {
            _S1, ///< tick_1
            _S2, ///< tick_2
            _S3, ///< tick_3
            _S4, ///< tick_4
            _S5, ///< tick_5
            _S6, ///< tick_6
            _S7, ///< tick_7
            NO   ///< tick_8
        };

        return {_tick_segments, static_cast<uint16_t>(Base::TickSegments::size)};
    }


    /// @brief Listing of tick segments
    /// @details The segments are listed in the same order as in the Base::OtherSegments
    static ArrayWrapper<uint8_t> _get_other_segments_map()
    {
        static constexpr uint8_t _other_segments[static_cast<uint16_t>(Base::OtherSegments::size)] =
        {
            _T1,  ///< tariff_word
            _T2,  ///< max_word
            _S8,  ///< low_battery
            _S9,  ///< reley_first_half
            _S10, ///< reley_second_half
            _T12, ///< time
            _T13, ///< date
        };

        return {_other_segments, static_cast<uint16_t>(Base::OtherSegments::size)};
    }
};

}