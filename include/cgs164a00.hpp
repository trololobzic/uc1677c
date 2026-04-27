#pragma once

#include "uc1677c.hpp"

namespace uc1677c
{

struct Cgs164a00Base
{

/// @brief List of raw segments. The order is defined in the datasheet.
enum Segments : uint8_t
{
    _13A, _P10, _14F, _14E, _14G, _14D, _14B, _14C, _14A, _P11, _15F, _15E, _15G, _15D, _15B, _15C,
    _15A, _P12, _16F, _16E, _16G, _16D, _16B, _16C, _16A, _P13, _17F, _17E, _17G, _17D, _17B, _17C,
    _17A, _P14, _T12, _T23, _T22, _T21, _T13, _T20, _T17, _T18, _T19, _T16, _T14, _T15,   _3,  _T6,
      _2,   _1, _T11,  _T5, _T10,  _T4,  _T9,  _T3,  _T8,  _T2,  _T7,  _T1,  _8D,  _P8,  _8C,  _8B,
     _8G,  _8A,  _8E,  _8F,  _7D,  _P7,  _7C,  _7B,  _7G,  _7A,  _7E,  _7F,  _6D,  _P6,  _6C,  _6B,
     _6G,  _6A,  _6E,  _6F,  _5D,  _P5,  _5C,  _5B,  _5G,  _5A,  _5E,  _5F,  _4D,  _P4,  _4C,  _4B,
     _4G,  _4A,  _4E,  _4F,  _3D,  _P3,  _3C,  _3B,  _3G,  _3A,  _3E,  _3F,  _2D,  _P2,  _2C,  _2B,
     _2G,  _2A,  _2E,  _2F,  _1D,  _P1,  _1C,  _1B,  _1G,  _1A,  _1E,  _1F,  _9A,  _S1,  _9F,  _9E,
     _9G,  _9D,  _9B,  _9C,  _S3,  _S5,  _S2,  _S4, _11A, _10A, _10F, _10E, _10G, _10D, _10B, _10C,
    _11F, _11E, _11G, _11D, _11B, _11C, _12F, _12E, _12G, _12D, _12B, _12C, _12A,  _P9, _13F, _13E,
    _13G, _13D, _13B, _13C,

    size
};

static constexpr uint16_t ram_size = helpers::Utils::number_of_bytes(Segments::size);
};


template<typename TI2C>
class Cgs164a00 : public DeviceDisplayBase<Uc1677cBase<TI2C, Cgs164a00Base::ram_size>, Cgs164a00<TI2C>>, public Cgs164a00Base
{
public:
    using Base = DeviceDisplayBase<Uc1677cBase<TI2C, Cgs164a00Base::ram_size>, Cgs164a00<TI2C>>;
    using Digit = typename Base::Digit;
    using CharacterStrings = typename Base::CharacterStrings;

    friend Base;

protected:
    constexpr static uint8_t NO = 0xFF;

    static helpers::ArrayWrapper<Digit> _get_string_segments_map(CharacterStrings where)
    {
        switch(where)
        {
            case CharacterStrings::main:
            {
                static constexpr auto _main_string_length = 8;
                static constexpr Digit _main_string_segments_map[_main_string_length] =
                {
                    {_10A, _10B, _10C, _10D, _10E, _10F, _10G,  NO },
                    {_11A, _11B, _11C, _11D, _11E, _11F, _11G,  NO },
                    {_12A, _12B, _12C, _12D, _12E, _12F, _12G, _P9 },
                    {_13A, _13B, _13C, _13D, _13E, _13F, _13G, _P10},
                    {_14A, _14B, _14C, _14D, _14E, _14F, _14G, _P11},
                    {_15A, _15B, _15C, _15D, _15E, _15F, _15G, _P12},
                    {_16A, _16B, _16C, _16D, _16E, _16F, _16G, _P13},
                    {_17A, _17B, _17C, _17D, _17E, _17F, _17G, _P14}
                };

                return {_main_string_segments_map, _main_string_length};
            }

            case CharacterStrings::additional1:
            {
                static constexpr auto _additional_string_length = 8;
                static constexpr Digit _additional_string_segments_map[_additional_string_length] =
                {
                    { _1A,  _1B,  _1C,  _1D,  _1E,  _1F,  _1G,  _P1},
                    { _2A,  _2B,  _2C,  _2D,  _2E,  _2F,  _2G,  _P2},
                    { _3A,  _3B,  _3C,  _3D,  _3E,  _3F,  _3G,  _P3},
                    { _4A,  _4B,  _4C,  _4D,  _4E,  _4F,  _4G,  _P4},
                    { _5A,  _5B,  _5C,  _5D,  _5E,  _5F,  _5G,  _P5},
                    { _6A,  _6B,  _6C,  _6D,  _6E,  _6F,  _6G,  _P6},
                    { _7A,  _7B,  _7C,  _7D,  _7E,  _7F,  _7G,  _P7},
                    { _8A,  _8B,  _8C,  _8D,  _8E,  _8F,  _8G,  _P8}
                };

                return {_additional_string_segments_map, _additional_string_length};
            }

            case CharacterStrings::tariff:
            {
                static constexpr auto _tariff_string_length = 1;
                static constexpr Digit _tariff_string_segments_map[_tariff_string_length] =
                {
                    { _9A,  _9B,  _9C,  _9D,  _9E,  _9F,  _9G,  NO}
                };

                return {_tariff_string_segments_map, _tariff_string_length};
            }

            default:
                return {nullptr, 0};
        }
    }


    /// @brief Listing of units segments
    /// @details The segments are listed in the same order as in the Base::UnitSegments
    static helpers::ArrayWrapper<uint8_t> _get_unit_segments_map()
    {
        static constexpr uint8_t _unit_segments[static_cast<uint16_t>(Base::UnitSegments::size)] =
        {
            _T12, ///< cos
            _T13, ///< percent
            _T14, ///< hz
            _T23, ///< m
            _T22, ///< g
            _T21, ///< k
            _T20, ///< w
            _T17, ///< a
            _T18, ///< t
            _T19, ///< -
            _T16, ///< r
            _T15  ///< h
        };

        return {_unit_segments, static_cast<uint16_t>(Base::UnitSegments::size)};
    }


    /// @brief Listing of phase segments
    /// @details The segments are listed in the same order as in the Base::PhaseSegments
    static helpers::ArrayWrapper<uint8_t> _get_phase_segments_map()
    {
        static constexpr uint8_t _phase_segments[static_cast<uint16_t>(Base::PhaseSegments::size)] =
        {
            _T11, ///< phase_word
            _1,  ///< phase_1
            _2,  ///< phase_2
            _3   ///< phase_3
        };

        return {_phase_segments, static_cast<uint16_t>(Base::PhaseSegments::size)};
    }


    /// @brief Listing of period segments
    /// @details The segments are listed in the same order as in the Base::PeriodSegments
    static helpers::ArrayWrapper<uint8_t> _get_period_segments_map()
    {
        static constexpr uint8_t _period_segments[static_cast<uint16_t>(Base::PeriodSegments::size)] =
        {
            _T1,  ///< begin
            _T2,  ///< last
            _T7,  ///< total
            _T8,  ///< year
            _T9,  ///< month
            _T10, ///< day
            NO,   ///< winter
            NO,   ///< summer
        };

        return {_period_segments, static_cast<uint16_t>(Base::PeriodSegments::size)};
    }


    /// @brief Listing of tick segments
    /// @details The segments are listed in the same order as in the Base::TickSegments
    static helpers::ArrayWrapper<uint8_t> _get_tick_segments_map()
    {
        const uint8_t _tick_segments[static_cast<uint16_t>(Base::TickSegments::size)] =
        {
            _T3, ///< tick_1
            _T4, ///< tick_2
            _T5, ///< tick_3
            _T6, ///< tick_4
            NO, ///< tick_5
            NO, ///< tick_6
            NO, ///< tick_7
            NO  ///< tick_8
        };

        return {_tick_segments, static_cast<uint16_t>(Base::TickSegments::size)};
    }


    /// @brief Listing of tick segments
    /// @details The segments are listed in the same order as in the Base::OtherSegments
    static helpers::ArrayWrapper<uint8_t> _get_other_segments_map()
    {
        const uint8_t _other_segments[static_cast<uint16_t>(Base::OtherSegments::size)] =
        {
            _S1, ///< tariff_word
            _S5, ///< max_word
            _S2, ///< low_battery
            _S4, ///< reley_first_half
            _S3, ///< reley_second_half
            NO,  ///< time
            NO   ///< date
        };

        return {_other_segments, static_cast<uint16_t>(Base::OtherSegments::size)};
    }
};

}