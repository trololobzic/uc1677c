#pragma once

#include "uc1677c.hpp"

namespace uc1677c
{

//S22 | S23 | S24 | S25 | S26 | S27 | S28 | S29 | S30 | S31 | S32 | S33 | S34 | S35 | S36 | S37 | S38 | S39 | S40 | S41 | S42 | S43
// 0  |  2  | 4   |  6  |  8  | 10  | 12  | 14  | 16  | 18  | 20  | 22  | 24  | 26  | 28  | 30  | 32  | 34  | 36  | 38  | 40  | 42
// 1  |  3  | 5   |  7  |  9  | 11  | 13  | 15  | 17  | 19  | 21  | 23  | 25  | 27  | 29  | 31  | 33  | 35  | 37  | 39  | 41  | 43

//S44 | S45 | S46 | S47 | S48 | S49 | S50 | S51 | S52 | S53 | S54 | S55 | S56 | S57 | S58 | S59 | S60 | S61 | S62 | S63 | S64 | S65
// 44 | 46  | 48  | 50  | 52  | 54  | 56  | 58  | 60  | 62  | 64  | 66  | 68  | 70  | 72  | 74  | 76  | 78  | 80  | 82  | 84  | 86
// 45 | 47  | 49  | 51  | 53  | 55  | 57  | 59  | 61  | 63  | 65  | 67  | 69  | 71  | 73  | 75  | 77  | 79  | 81  | 83  | 85  | 87

//S66 | S67 | S68 | S69 | S70 | S71 | S72 | S73 | S74 | S75 | S76 | S77 | S78 | S79 | S80 | S81 | S82 | S83 | S84 | S85 | S86 | S87
//88  | 90  | 92  | 94  | 96  | 98  | 100 | 102 | 104 | 106 | 108 | 110 | 112 | 114 | 116 | 118 | 120 | 122 | 124 | 126 | 128 | 130
//89  | 91  | 93  | 95  | 97  | 99  | 101 | 103 | 105 | 107 | 109 | 111 | 113 | 115 | 117 | 119 | 121 | 123 | 125 | 127 | 129 | 131

//S88 | S89 | S90 | S91 | S92 | S93 | S94 | S95 | S96 | S97 | S98 | S99 | S100| S101| S102| S103| S104| S105| S106| S107| S108| S109
//132 | 134 | 136 | 138 | 140 | 142 | 144 | 146 | 148 | 150 | 152 | 154 | 156 | 158 | 160 | 162 | 164 | 166 | 168 | 170 | 172 | 174
//133 | 135 | 137 | 139 | 141 | 143 | 145 | 147 | 149 | 151 | 153 | 155 | 157 | 159 | 161 | 163 | 165 | 167 | 169 | 171 | 173 | 175

//S110| S111| S112| S113| S114| S115| S116| S117| S118| S119| S120| S121| S122| S123| S124| S125| S126| S127| S128| S129| S130
//176 | 178 | 180 | 182 | 184 | 186 | 188 | 190 | 192 | 194 | 196 | 198 | 200 | 202 | 204 | 206 | 208 | 210 | 212 | 214 | 216
//177 | 179 | 181 | 183 | 185 | 187 | 189 | 191 | 193 | 195 | 197 | 199 | 201 | 203 | 205 | 207 | 209 | 211 | 213 | 215 | 217

constexpr uint16_t cgs214a06_ram_size = Utils::number_of_bytes(218);

template<typename TI2C>
class Cgs214a06 : public DeviceDisplayBase<Uc1677cBase<TI2C, cgs214a06_ram_size>, Cgs214a06<TI2C>>
{
public:
    using Base = DeviceDisplayBase<Uc1677cBase<TI2C, cgs214a06_ram_size>, Cgs214a06<TI2C>>;
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
                //     A    B    C    D    E    F    G  DOT
                    { 79,  71,  70,  68,  66,  67,  69,  NO},
                    { 78,  77,  76,  74,  72,  73,  75,  NO},
                    { 89,  87,  86,  84,  82,  83,  85,  88},
                    { 97,  95,  94,  92,  90,  91,  93,  96},
                    {107, 105, 104, 102, 100, 101, 103, 106},
                    {115, 113, 112, 110, 108, 109, 111, 114},
                    {123, 121, 120, 118, 116, 117, 119, 122},
                    {133, 131, 130, 128, 126, 127, 129, 132}
                };

                return {_main_string_segments_map, _main_string_length};
            }

            case CharacterStrings::additional1:
            {
                static constexpr uint16_t _additional_string_1_length = 8;
                static constexpr Digit _additional_string_1_segments_map[_additional_string_1_length] =
                {
                    { 54,  52,  53,  51,  57,  56,  55,  50},
                    { 44,  42,  43,  41,  47,  46,  45,  40},
                    { 36,  34,  35,  33,  39,  38,  37,  32},
                    { 28,  26,  27,  25,  31,  30,  29,  24},
                    { 18,  16,  17,  15,  21,  20,  19,  14},
                    { 10,   8,   9,   7,  13,  12,  11,   6},
                    {  2,   0,   1, 215,   5,   4,   3, 214},
                    {210, 208, 209, 207, 213, 212, 211, 206}
                };

                return {_additional_string_1_segments_map, _additional_string_1_length};
            }

            case CharacterStrings::additional2:
            {
                static constexpr uint16_t _additional_string_2_length = 6;
                static constexpr Digit _additional_string_2_segments_map[_additional_string_2_length] =
                {
                    {196, 194, 195, 192, 199, 198, 197,  NO},
                    {188, 186, 187, 193, 191, 190, 189, 185},
                    {180, 178, 179, 185, 183, 182, 181,  NO},
                    {170, 168, 169, 174, 173, 172, 171, 166},
                    {162, 160, 161, 167, 165, 164, 163,  NO},
                    {154, 152, 153, 158, 157, 156, 155,  NO}
                };

                return {_additional_string_2_segments_map, _additional_string_2_length};
            }

            case CharacterStrings::tariff:
            {
                static constexpr uint16_t _tariff_string_length = 1;
                static constexpr Digit _tariff_string_segments_map[_tariff_string_length] =
                {
                    { 60,  58,  59,  65,  63,  62,  61, NO}
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
            139, ///< cos
            143, ///< percent
            149, ///< hz
            134, ///< m
            136, ///< g
            138, ///< k
            140, ///< w
            144, ///< a
            142, ///< t
            146, ///< -
            148, ///< r
            150  ///< h
        };

        return {_unit_segments, static_cast<uint16_t>(Base::UnitSegments::size)};
    }

    static ArrayWrapper<uint8_t> _get_phase_segments_map()
    {
        /// @brief Listing of phase segments
        /// @details The segments are listed in the same order as in the Base::PhaseSegments
        static constexpr uint8_t _phase_segments[static_cast<uint16_t>(Base::PhaseSegments::size)] =
        {
            204, ///< phase_word
            205, ///< phase_1
            203, ///< phase_2
            202  ///< phase_3
        };

        return {_phase_segments, static_cast<uint16_t>(Base::PhaseSegments::size)};
    }

    static ArrayWrapper<uint8_t> _get_period_segments_map()
    {
        /// @brief Listing of period segments
        /// @details The segments are listed in the same order as in the Base::PeriodSegments
        static constexpr uint8_t _period_segments[static_cast<uint16_t>(Base::PeriodSegments::size)] =
        {
            81,  ///< begin
            98,  ///< last
            80,  ///< total
            99,  ///< year
            124, ///< month
            125, ///< day
            135, ///< winter
            137  ///< summer
        };

        return {_period_segments, static_cast<uint16_t>(Base::PeriodSegments::size)};
    }

    static ArrayWrapper<uint8_t> _get_tick_segments_map()
    {
        /// @brief Listing of tick segments
        /// @details The segments are listed in the same order as in the Base::TickSegments
        static constexpr uint8_t _tick_segments[static_cast<uint16_t>(Base::TickSegments::size)] =
        {
            49,  ///< tick_1
            22,  ///< tick_2
            23,  ///< tick_3
            217, ///< tick_4
            216, ///< tick_5
            201, ///< tick_6
            176, ///< tick_7
            NO   ///< tick_8
        };

        return {_tick_segments, static_cast<uint16_t>(Base::TickSegments::size)};
    }

    static ArrayWrapper<uint8_t> _get_other_segments_map()
    {
        /// @brief Listing of tick segments
        /// @details The segments are listed in the same order as in the Base::OtherSegments
        static constexpr uint8_t _other_segments[static_cast<uint16_t>(Base::OtherSegments::size)] =
        {
            48,  ///< tariff_word
            64,  ///< max_word
            141, ///< low_battery
            145, ///< reley_first_half
            151, ///< reley_second_half
            200, ///< time
            177, ///< date
        };

        return {_other_segments, static_cast<uint16_t>(Base::OtherSegments::size)};
    }
};

}