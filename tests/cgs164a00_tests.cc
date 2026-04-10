#include <source_location>
#include "doctest/doctest.h"
#include "test_utils.hpp"
#include "cgs164a00.hpp"


using Mock = uc1677c::tests::I2C_ram_mock;
using Lcd = uc1677c::Cgs164a00<Mock>;
using Segments = Lcd::Segments;

TEST_CASE("cgs164a00 methods")
{
    Lcd lcd;
    auto check_helper = [&](auto print_wrapper, std::vector<size_t> && expected_ram_state, std::source_location location = std::source_location::current())
    {
        CAPTURE(Mock::ram);
        INFO("Assert failed at: " << std::string_view(location.file_name()) << ":" << location.line());
        Mock::ram.clear();
        lcd.clear_all();
        print_wrapper();
        lcd.update();
        CHECK(Mock::check_ram(expected_ram_state));
    };

    SUBCASE("print int")
    {
        check_helper([&lcd]{ lcd.print(Lcd::CharacterStrings::main, 1); }, {Segments::_17B, Segments::_17C});
        check_helper([&lcd]{ lcd.print(Lcd::CharacterStrings::main, 12); }, {Segments::_16B, Segments::_16C,
                            Segments::_17A, Segments::_17B, Segments::_17G, Segments::_17E, Segments::_17D});

        check_helper([&lcd]{ lcd.print(Lcd::CharacterStrings::main, 123); }, {Segments::_15B, Segments::_15C,
                            Segments::_16A, Segments::_16B, Segments::_16G, Segments::_16E, Segments::_16D,
                            Segments::_17A, Segments::_17B, Segments::_17C, Segments::_17D, Segments::_17G});

        check_helper([&lcd]{ lcd.print(Lcd::CharacterStrings::main, 1234); }, {Segments::_14B, Segments::_14C,
                            Segments::_15A, Segments::_15B, Segments::_15G, Segments::_15E, Segments::_15D,
                            Segments::_16A, Segments::_16B, Segments::_16C, Segments::_16D, Segments::_16G,
                            Segments::_17F, Segments::_17G, Segments::_17B, Segments::_17C});

        check_helper([&lcd]{ lcd.print(Lcd::CharacterStrings::main, 12345); }, {Segments::_13B, Segments::_13C,
                            Segments::_14A, Segments::_14B, Segments::_14G, Segments::_14E, Segments::_14D,
                            Segments::_15A, Segments::_15B, Segments::_15C, Segments::_15D, Segments::_15G,
                            Segments::_16F, Segments::_16G, Segments::_16B, Segments::_16C,
                            Segments::_17A, Segments::_17F, Segments::_17G, Segments::_17C, Segments::_17D});

        check_helper([&lcd]{ lcd.print(Lcd::CharacterStrings::main, 123456); }, {Segments::_12B, Segments::_12C,
                            Segments::_13A, Segments::_13B, Segments::_13G, Segments::_13E, Segments::_13D,
                            Segments::_14A, Segments::_14B, Segments::_14C, Segments::_14D, Segments::_14G,
                            Segments::_15F, Segments::_15G, Segments::_15B, Segments::_15C,
                            Segments::_16A, Segments::_16F, Segments::_16G, Segments::_16C, Segments::_16D,
                            Segments::_17A, Segments::_17F, Segments::_17G, Segments::_17C, Segments::_17D, Segments::_17E});

        check_helper([&lcd]{ lcd.print(Lcd::CharacterStrings::main, 1234567); }, {Segments::_11B, Segments::_11C,
                            Segments::_12A, Segments::_12B, Segments::_12G, Segments::_12E, Segments::_12D,
                            Segments::_13A, Segments::_13B, Segments::_13C, Segments::_13D, Segments::_13G,
                            Segments::_14F, Segments::_14G, Segments::_14B, Segments::_14C,
                            Segments::_15A, Segments::_15F, Segments::_15G, Segments::_15C, Segments::_15D,
                            Segments::_16A, Segments::_16F, Segments::_16G, Segments::_16C, Segments::_16D, Segments::_16E,
                            Segments::_17A, Segments::_17B, Segments::_17C});

        check_helper([&lcd]{ lcd.print(Lcd::CharacterStrings::main, 12345678); }, {Segments::_10B, Segments::_10C,
                            Segments::_11A, Segments::_11B, Segments::_11G, Segments::_11E, Segments::_11D,
                            Segments::_12A, Segments::_12B, Segments::_12C, Segments::_12D, Segments::_12G,
                            Segments::_13F, Segments::_13G, Segments::_13B, Segments::_13C,
                            Segments::_14A, Segments::_14F, Segments::_14G, Segments::_14C, Segments::_14D,
                            Segments::_15A, Segments::_15F, Segments::_15G, Segments::_15C, Segments::_15D, Segments::_15E,
                            Segments::_16A, Segments::_16B, Segments::_16C,
                            Segments::_17A, Segments::_17B, Segments::_17C, Segments::_17D, Segments::_17E, Segments::_17F, Segments::_17G});

        check_helper([&lcd]{ lcd.print(Lcd::CharacterStrings::main, -12345678); }, {Segments::_10B, Segments::_10C,
                            Segments::_11A, Segments::_11B, Segments::_11G, Segments::_11E, Segments::_11D,
                            Segments::_12A, Segments::_12B, Segments::_12C, Segments::_12D, Segments::_12G,
                            Segments::_13F, Segments::_13G, Segments::_13B, Segments::_13C,
                            Segments::_14A, Segments::_14F, Segments::_14G, Segments::_14C, Segments::_14D,
                            Segments::_15A, Segments::_15F, Segments::_15G, Segments::_15C, Segments::_15D, Segments::_15E,
                            Segments::_16A, Segments::_16B, Segments::_16C,
                            Segments::_17A, Segments::_17B, Segments::_17C, Segments::_17D, Segments::_17E, Segments::_17F, Segments::_17G});
    }

    SUBCASE("print float")
    {
        //TODO
    }

    SUBCASE("print c-string")
    {
        check_helper([&lcd]{ lcd.print(Lcd::CharacterStrings::main, "abc.defgh"); }, {Segments::_10A, Segments::_10B, Segments::_10C, Segments::_10E, Segments::_10F, Segments::_10G,
                            Segments::_11C, Segments::_11D, Segments::_11E, Segments::_11F, Segments::_11G,
                            Segments::_12A, Segments::_12D, Segments::_12E, Segments::_12F, Segments::_P9,
                            Segments::_13B, Segments::_13C, Segments::_13D, Segments::_13E, Segments::_13G,
                            Segments::_14A, Segments::_14D, Segments::_14E, Segments::_14F, Segments::_14G,
                            Segments::_15A, Segments::_15E, Segments::_15F, Segments::_15G,
                            Segments::_16A, Segments::_16C, Segments::_16D, Segments::_16E, Segments::_16F,
                            Segments::_17B, Segments::_17C, Segments::_17E, Segments::_17F, Segments::_17G});

        check_helper([&lcd]{ lcd.print(Lcd::CharacterStrings::main, "ijkl.mnop"); }, {Segments::_10B, Segments::_10C,
                            Segments::_11B, Segments::_11C, Segments::_11D,
                            Segments::_12A, Segments::_12C, Segments::_12E, Segments::_12F, Segments::_12G,
                            Segments::_13D, Segments::_13E, Segments::_13F, Segments::_P10,
                            Segments::_14A, Segments::_14C, Segments::_14E, Segments::_14G,
                            Segments::_15C, Segments::_15E, Segments::_15G,
                            Segments::_16A, Segments::_16B, Segments::_16C, Segments::_16D, Segments::_16E, Segments::_16F,
                            Segments::_17A, Segments::_17B, Segments::_17E, Segments::_17F, Segments::_17G});

        check_helper([&lcd]{ lcd.print(Lcd::CharacterStrings::main, "qrstu.vwx"); }, {Segments::_10A, Segments::_10B, Segments::_10C, Segments::_10F, Segments::_10G,
                            Segments::_11E, Segments::_11G,
                            Segments::_12A, Segments::_12C, Segments::_12D, Segments::_12F, Segments::_12G,
                            Segments::_13D, Segments::_13E, Segments::_13F, Segments::_13G,
                            Segments::_14C, Segments::_14D, Segments::_14E, Segments::_P11,
                            Segments::_15B, Segments::_15C, Segments::_15D, Segments::_15E, Segments::_15F,
                            Segments::_16B, Segments::_16D, Segments::_16F, Segments::_16G,
                            Segments::_17B, Segments::_17C, Segments::_17E, Segments::_17F, Segments::_17G});

        check_helper([&lcd]{ lcd.print(Lcd::CharacterStrings::main, "yz1234.56"); }, {Segments::_10B, Segments::_10E, Segments::_10F, Segments::_10G,
                            Segments::_11A, Segments::_11B, Segments::_11D, Segments::_11E, Segments::_11G,
                            Segments::_12B, Segments::_12C,
                            Segments::_13A, Segments::_13B, Segments::_13D, Segments::_13E, Segments::_13G,
                            Segments::_14A, Segments::_14B, Segments::_14C, Segments::_14D, Segments::_14G,
                            Segments::_15B, Segments::_15C, Segments::_15F, Segments::_15G, Segments::_P12,
                            Segments::_16A, Segments::_16C, Segments::_16D, Segments::_16F, Segments::_16G,
                            Segments::_17A, Segments::_17C, Segments::_17D, Segments::_17E, Segments::_17F, Segments::_17G});

        check_helper([&lcd]{ lcd.print(Lcd::CharacterStrings::main, "7890_=~.'"); }, {Segments::_10A, Segments::_10B, Segments::_10C,
                            Segments::_11A, Segments::_11B, Segments::_11C, Segments::_11D, Segments::_11E, Segments::_11F, Segments::_11G,
                            Segments::_12A, Segments::_12B, Segments::_12C, Segments::_12D, Segments::_12F, Segments::_12G,
                            Segments::_13A, Segments::_13B, Segments::_13C, Segments::_13D, Segments::_13E, Segments::_13F,
                            Segments::_14D,
                            Segments::_15D, Segments::_15G,
                            Segments::_16A, Segments::_P13,
                            Segments::_17B});
    }
}

TEST_CASE("cgs164a00 defines")
{
    CHECK(static_cast<size_t>(Segments::_13A) == 0);
    CHECK(static_cast<size_t>(Segments::_P10) == 1);
    CHECK(static_cast<size_t>(Segments::_14F) == 2);
    CHECK(static_cast<size_t>(Segments::_14E) == 3);
    CHECK(static_cast<size_t>(Segments::_14G) == 4);
    CHECK(static_cast<size_t>(Segments::_14D) == 5);
    CHECK(static_cast<size_t>(Segments::_14B) == 6);
    CHECK(static_cast<size_t>(Segments::_14C) == 7);
    CHECK(static_cast<size_t>(Segments::_14A) == 8);
    CHECK(static_cast<size_t>(Segments::_P11) == 9);
    CHECK(static_cast<size_t>(Segments::_15F) == 10);
    CHECK(static_cast<size_t>(Segments::_15E) == 11);
    CHECK(static_cast<size_t>(Segments::_15G) == 12);
    CHECK(static_cast<size_t>(Segments::_15D) == 13);
    CHECK(static_cast<size_t>(Segments::_15B) == 14);
    CHECK(static_cast<size_t>(Segments::_15C) == 15);
    CHECK(static_cast<size_t>(Segments::_15A) == 16);
    CHECK(static_cast<size_t>(Segments::_P12) == 17);
    CHECK(static_cast<size_t>(Segments::_16F) == 18);
    CHECK(static_cast<size_t>(Segments::_16E) == 19);
    CHECK(static_cast<size_t>(Segments::_16G) == 20);
    CHECK(static_cast<size_t>(Segments::_16D) == 21);
    CHECK(static_cast<size_t>(Segments::_16B) == 22);
    CHECK(static_cast<size_t>(Segments::_16C) == 23);
    CHECK(static_cast<size_t>(Segments::_16A) == 24);
    CHECK(static_cast<size_t>(Segments::_P13) == 25);
    CHECK(static_cast<size_t>(Segments::_17F) == 26);
    CHECK(static_cast<size_t>(Segments::_17E) == 27);
    CHECK(static_cast<size_t>(Segments::_17G) == 28);
    CHECK(static_cast<size_t>(Segments::_17D) == 29);
    CHECK(static_cast<size_t>(Segments::_17B) == 30);
    CHECK(static_cast<size_t>(Segments::_17C) == 31);
    CHECK(static_cast<size_t>(Segments::_17A) == 32);
    CHECK(static_cast<size_t>(Segments::_P14) == 33);
    CHECK(static_cast<size_t>(Segments::_T12) == 34);
    CHECK(static_cast<size_t>(Segments::_T23) == 35);
    CHECK(static_cast<size_t>(Segments::_T22) == 36);
    CHECK(static_cast<size_t>(Segments::_T21) == 37);
    CHECK(static_cast<size_t>(Segments::_T13) == 38);
    CHECK(static_cast<size_t>(Segments::_T20) == 39);
    CHECK(static_cast<size_t>(Segments::_T17) == 40);
    CHECK(static_cast<size_t>(Segments::_T18) == 41);
    CHECK(static_cast<size_t>(Segments::_T19) == 42);
    CHECK(static_cast<size_t>(Segments::_T16) == 43);
    CHECK(static_cast<size_t>(Segments::_T14) == 44);
    CHECK(static_cast<size_t>(Segments::_T15) == 45);
    CHECK(static_cast<size_t>(Segments::_3  ) == 46);
    CHECK(static_cast<size_t>(Segments::_T6 ) == 47);
    CHECK(static_cast<size_t>(Segments::_2  ) == 48);
    CHECK(static_cast<size_t>(Segments::_1  ) == 49);
    CHECK(static_cast<size_t>(Segments::_T11) == 50);
    CHECK(static_cast<size_t>(Segments::_T5 ) == 51);
    CHECK(static_cast<size_t>(Segments::_T10) == 52);
    CHECK(static_cast<size_t>(Segments::_T4 ) == 53);
    CHECK(static_cast<size_t>(Segments::_T9 ) == 54);
    CHECK(static_cast<size_t>(Segments::_T3 ) == 55);
    CHECK(static_cast<size_t>(Segments::_T8 ) == 56);
    CHECK(static_cast<size_t>(Segments::_T2 ) == 57);
    CHECK(static_cast<size_t>(Segments::_T7 ) == 58);
    CHECK(static_cast<size_t>(Segments::_T1 ) == 59);
    CHECK(static_cast<size_t>(Segments::_8D ) == 60);
    CHECK(static_cast<size_t>(Segments::_P8 ) == 61);
    CHECK(static_cast<size_t>(Segments::_8C ) == 62);
    CHECK(static_cast<size_t>(Segments::_8B ) == 63);
    CHECK(static_cast<size_t>(Segments::_8G ) == 64);
    CHECK(static_cast<size_t>(Segments::_8A ) == 65);
    CHECK(static_cast<size_t>(Segments::_8E ) == 66);
    CHECK(static_cast<size_t>(Segments::_8F ) == 67);
    CHECK(static_cast<size_t>(Segments::_7D ) == 68);
    CHECK(static_cast<size_t>(Segments::_P7 ) == 69);
    CHECK(static_cast<size_t>(Segments::_7C ) == 70);
    CHECK(static_cast<size_t>(Segments::_7B ) == 71);
    CHECK(static_cast<size_t>(Segments::_7G ) == 72);
    CHECK(static_cast<size_t>(Segments::_7A ) == 73);
    CHECK(static_cast<size_t>(Segments::_7E ) == 74);
    CHECK(static_cast<size_t>(Segments::_7F ) == 75);
    CHECK(static_cast<size_t>(Segments::_6D ) == 76);
    CHECK(static_cast<size_t>(Segments::_P6 ) == 77);
    CHECK(static_cast<size_t>(Segments::_6C ) == 78);
    CHECK(static_cast<size_t>(Segments::_6B ) == 79);
    CHECK(static_cast<size_t>(Segments::_6G ) == 80);
    CHECK(static_cast<size_t>(Segments::_6A ) == 81);
    CHECK(static_cast<size_t>(Segments::_6E ) == 82);
    CHECK(static_cast<size_t>(Segments::_6F ) == 83);
    CHECK(static_cast<size_t>(Segments::_5D ) == 84);
    CHECK(static_cast<size_t>(Segments::_P5 ) == 85);
    CHECK(static_cast<size_t>(Segments::_5C ) == 86);
    CHECK(static_cast<size_t>(Segments::_5B ) == 87);
    CHECK(static_cast<size_t>(Segments::_5G ) == 88);
    CHECK(static_cast<size_t>(Segments::_5A ) == 89);
    CHECK(static_cast<size_t>(Segments::_5E ) == 90);
    CHECK(static_cast<size_t>(Segments::_5F ) == 91);
    CHECK(static_cast<size_t>(Segments::_4D ) == 92);
    CHECK(static_cast<size_t>(Segments::_P4 ) == 93);
    CHECK(static_cast<size_t>(Segments::_4C ) == 94);
    CHECK(static_cast<size_t>(Segments::_4B ) == 95);
    CHECK(static_cast<size_t>(Segments::_4G ) == 96);
    CHECK(static_cast<size_t>(Segments::_4A ) == 97);
    CHECK(static_cast<size_t>(Segments::_4E ) == 98);
    CHECK(static_cast<size_t>(Segments::_4F ) == 99);
    CHECK(static_cast<size_t>(Segments::_3D ) == 100);
    CHECK(static_cast<size_t>(Segments::_P3 ) == 101);
    CHECK(static_cast<size_t>(Segments::_3C ) == 102);
    CHECK(static_cast<size_t>(Segments::_3B ) == 103);
    CHECK(static_cast<size_t>(Segments::_3G ) == 104);
    CHECK(static_cast<size_t>(Segments::_3A ) == 105);
    CHECK(static_cast<size_t>(Segments::_3E ) == 106);
    CHECK(static_cast<size_t>(Segments::_3F ) == 107);
    CHECK(static_cast<size_t>(Segments::_2D ) == 108);
    CHECK(static_cast<size_t>(Segments::_P2 ) == 109);
    CHECK(static_cast<size_t>(Segments::_2C ) == 110);
    CHECK(static_cast<size_t>(Segments::_2B ) == 111);
    CHECK(static_cast<size_t>(Segments::_2G ) == 112);
    CHECK(static_cast<size_t>(Segments::_2A ) == 113);
    CHECK(static_cast<size_t>(Segments::_2E ) == 114);
    CHECK(static_cast<size_t>(Segments::_2F ) == 115);
    CHECK(static_cast<size_t>(Segments::_1D ) == 116);
    CHECK(static_cast<size_t>(Segments::_P1 ) == 117);
    CHECK(static_cast<size_t>(Segments::_1C ) == 118);
    CHECK(static_cast<size_t>(Segments::_1B ) == 119);
    CHECK(static_cast<size_t>(Segments::_1G ) == 120);
    CHECK(static_cast<size_t>(Segments::_1A ) == 121);
    CHECK(static_cast<size_t>(Segments::_1E ) == 122);
    CHECK(static_cast<size_t>(Segments::_1F ) == 123);
    CHECK(static_cast<size_t>(Segments::_9A ) == 124);
    CHECK(static_cast<size_t>(Segments::_S1 ) == 125);
    CHECK(static_cast<size_t>(Segments::_9F ) == 126);
    CHECK(static_cast<size_t>(Segments::_9E ) == 127);
    CHECK(static_cast<size_t>(Segments::_9G ) == 128);
    CHECK(static_cast<size_t>(Segments::_9D ) == 129);
    CHECK(static_cast<size_t>(Segments::_9B ) == 130);
    CHECK(static_cast<size_t>(Segments::_9C ) == 131);
    CHECK(static_cast<size_t>(Segments::_S3 ) == 132);
    CHECK(static_cast<size_t>(Segments::_S5 ) == 133);
    CHECK(static_cast<size_t>(Segments::_S2 ) == 134);
    CHECK(static_cast<size_t>(Segments::_S4 ) == 135);
    CHECK(static_cast<size_t>(Segments::_11A) == 136);
    CHECK(static_cast<size_t>(Segments::_10A) == 137);
    CHECK(static_cast<size_t>(Segments::_10F) == 138);
    CHECK(static_cast<size_t>(Segments::_10E) == 139);
    CHECK(static_cast<size_t>(Segments::_10G) == 140);
    CHECK(static_cast<size_t>(Segments::_10D) == 141);
    CHECK(static_cast<size_t>(Segments::_10B) == 142);
    CHECK(static_cast<size_t>(Segments::_10C) == 143);
    CHECK(static_cast<size_t>(Segments::_11F) == 144);
    CHECK(static_cast<size_t>(Segments::_11E) == 145);
    CHECK(static_cast<size_t>(Segments::_11G) == 146);
    CHECK(static_cast<size_t>(Segments::_11D) == 147);
    CHECK(static_cast<size_t>(Segments::_11B) == 148);
    CHECK(static_cast<size_t>(Segments::_11C) == 149);
    CHECK(static_cast<size_t>(Segments::_12F) == 150);
    CHECK(static_cast<size_t>(Segments::_12E) == 151);
    CHECK(static_cast<size_t>(Segments::_12G) == 152);
    CHECK(static_cast<size_t>(Segments::_12D) == 153);
    CHECK(static_cast<size_t>(Segments::_12B) == 154);
    CHECK(static_cast<size_t>(Segments::_12C) == 155);
    CHECK(static_cast<size_t>(Segments::_12A) == 156);
    CHECK(static_cast<size_t>(Segments::_P9 ) == 157);
    CHECK(static_cast<size_t>(Segments::_13F) == 158);
    CHECK(static_cast<size_t>(Segments::_13E) == 159);
    CHECK(static_cast<size_t>(Segments::_13G) == 160);
    CHECK(static_cast<size_t>(Segments::_13D) == 161);
    CHECK(static_cast<size_t>(Segments::_13B) == 162);
    CHECK(static_cast<size_t>(Segments::_13C) == 163);
}
