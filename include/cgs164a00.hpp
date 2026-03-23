#pragma once

#include "uc1677c.hpp"

namespace uc1677c
{

//S40  | S41 | S42 | S43 | S44 | S45 | S46 | S47 | S48 | S49 | S50 | S51 | S52 | S53 | S54 | S55 | S56 | S57 | S58 | S59 | S60
// 0   |  2  | 4   |  6  |  8  | 10  | 12  | 14  | 16  | 18  | 20  | 22  | 24  | 26  | 28  | 30  | 32  | 34  | 36  | 38  | 40
// 1   |  3  | 5   |  7  |  9  | 11  | 13  | 15  | 17  | 19  | 21  | 23  | 25  | 27  | 29  | 31  | 33  | 35  | 37  | 39  | 41

//S61  | S62 | S63 | S64 | S65 | S66 | S67 | S68 | S69 | S70 | S71 | S72 | S73 | S74 | S75 | S76 | S77 | S78 | S79 | S80 | S81
// 42  |  44 | 46  |  48 | 50  | 52  | 54  | 56  | 58  | 60  | 62  | 64  | 66  | 68  | 70  | 72  | 74  | 76  | 78  | 80  | 82
// 43  |  45 | 47  |  49 | 51  | 53  | 55  | 57  | 59  | 61  | 63  | 65  | 67  | 69  | 71  | 73  | 75  | 77  | 79  | 81  | 83

//S82  | S83 | S84 | S85 | S86 | S87 | S88 | S89 | S90 | S91 | S92 | S93 | S94 | S95 | S96 | S97 | S98 | S99 | S100| S101| S102
// 84  |  86 | 88  |  90 | 92  | 94  | 96  | 98  | 100 | 102 | 104 | 106 | 108 | 110 | 112 | 114 | 116 | 118 | 120 | 122 | 124
// 85  |  87 | 89  |  91 | 93  | 95  | 97  | 99  | 101 | 103 | 105 | 107 | 109 | 111 | 113 | 115 | 117 | 119 | 121 | 123 | 125

//S103 | S104| S105| S106| S107| S108| S109| S110| S111| S112| S113| S114| S115| S116| S117| S118| S119| S120| S121
// 126 | 128 | 130 | 132 | 134 | 136 | 138 | 140 | 142 | 144 | 146 | 148 | 150 | 152 | 154 | 156 | 158 | 160 | 162
// 127 | 129 | 131 | 133 | 135 | 137 | 139 | 141 | 143 | 145 | 147 | 149 | 151 | 153 | 155 | 157 | 159 | 161 | 163

struct Cgs164a00Base
{
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

static constexpr uint16_t ram_size = Utils::number_of_bytes(Segments::size);
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

    static ArrayWrapper<Digit> _get_string_segments_map(CharacterStrings where)
    {
        switch(where)
        {
            case CharacterStrings::main:
            {
                static constexpr auto _main_string_length = 8;
                static constexpr Digit _main_string_segments_map[_main_string_length] =
                {
                //     A    B    C    D    E    F    G  DOT
                    {137, 142, 143, 141, 139, 138, 140,  NO},
                    {136, 148, 149, 147, 145, 144, 146,  NO},
                    {156, 154, 155, 153, 151, 150, 152, 157},
                    {  0, 162, 163, 161, 159, 158, 160,   1},
                    {  8,   6,   7,   5,   3,   2,   4,   9},
                    { 16,  14,  15,  13,  11,  10,  12,  17},
                    { 24,  22,  23,  21,  19,  18,  20,  25},
                    { 32,  30,  31,  29,  27,  26,  28,  33}
                };

                return {_main_string_segments_map, _main_string_length};
            }

            case CharacterStrings::additional1:
            {
                static constexpr auto _additional_string_length = 8;
                static constexpr Digit _additional_string_segments_map[_additional_string_length] =
                {
                    {121, 119, 118, 116, 122, 123, 120, 117 },
                    {113, 111, 110, 108, 114, 115, 112, 109 },
                    {105, 103, 102, 100, 106, 107, 104, 101 },
                    { 97,  95,  94,  92,  98,  99,  96,  93 },
                    { 89,  87,  86,  84,  90,  91,  88,  85 },
                    { 81,  79,  78,  76,  82,  83,  80,  77 },
                    { 73,  71,  70,  68,  74,  75,  72,  69 },
                    { 65,  63,  62,  60,  66,  67,  64,  61 }
                };

                return {_additional_string_segments_map, _additional_string_length};
            }

            case CharacterStrings::tariff:
            {
                static constexpr auto _tariff_string_length = 1;
                static constexpr Digit _tariff_string_segments_map[_tariff_string_length] =
                {
                    {124, 130, 131, 129, 127, 126, 128, NO}
                };

                return {_tariff_string_segments_map, _tariff_string_length};
            }

            default:
                return {nullptr, 0};
        }
    }

    static ArrayWrapper<uint8_t> _get_unit_segments_map()
    {
        /// @brief Listing of units segments
        /// @details The segments are listed in the same order as in the Base::UnitSegments
        static constexpr uint8_t _unit_segments[static_cast<uint16_t>(Base::UnitSegments::size)] =
        {
            34, ///< cos
            38, ///< percent
            44, ///< hz
            35, ///< m
            36, ///< g
            37, ///< k
            39, ///< w
            40, ///< a
            41, ///< t
            42, ///< -
            43, ///< r
            45  ///< h
        };

        return {_unit_segments, static_cast<uint16_t>(Base::UnitSegments::size)};
    }

    static ArrayWrapper<uint8_t> _get_phase_segments_map()
    {
        /// @brief Listing of phase segments
        /// @details The segments are listed in the same order as in the Base::PhaseSegments
        static constexpr uint8_t _phase_segments[static_cast<uint16_t>(Base::PhaseSegments::size)] =
        {
            50, ///< phase_word
            49, ///< phase_1
            48, ///< phase_2
            46  ///< phase_3
        };

        return {_phase_segments, static_cast<uint16_t>(Base::PhaseSegments::size)};
    }

    static ArrayWrapper<uint8_t> _get_period_segments_map()
    {
        /// @brief Listing of period segments
        /// @details The segments are listed in the same order as in the Base::PeriodSegments
        static constexpr uint8_t _period_segments[static_cast<uint16_t>(Base::PeriodSegments::size)] =
        {
            59, ///< begin
            57, ///< last
            58, ///< total
            56, ///< year
            54, ///< month
            52, ///< day
            NO, ///< winter
            NO, ///< summer
        };

        return {_period_segments, static_cast<uint16_t>(Base::PeriodSegments::size)};
    }

    static ArrayWrapper<uint8_t> _get_tick_segments_map()
    {
        /// @brief Listing of tick segments
        /// @details The segments are listed in the same order as in the Base::TickSegments
        const uint8_t _tick_segments[static_cast<uint16_t>(Base::TickSegments::size)] =
        {
            55, ///< tick_1
            53, ///< tick_2
            51, ///< tick_3
            47, ///< tick_4
            NO, ///< tick_5
            NO, ///< tick_6
            NO, ///< tick_7
            NO  ///< tick_8
        };

        return {_tick_segments, static_cast<uint16_t>(Base::TickSegments::size)};
    }

    static ArrayWrapper<uint8_t> _get_other_segments_map()
    {
        /// @brief Listing of tick segments
        /// @details The segments are listed in the same order as in the Base::OtherSegments
        const uint8_t _other_segments[static_cast<uint16_t>(Base::OtherSegments::size)] =
        {
            125, ///< tariff_word
            133, ///< max_word
            134, ///< low_battery
            135, ///< reley_first_half
            132, ///< reley_second_half
            NO,  ///< time
            NO   ///< date
        };

        return {_other_segments, static_cast<uint16_t>(Base::OtherSegments::size)};
    }
};

}