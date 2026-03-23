#include "doctest/doctest.h"
#include "test_utils.hpp"
#include "cgs164a00.hpp"

namespace uc1677c::test
{

}

TEST_CASE("cgs164a00")
{
    using Mock = uc1677c::tests::I2C_ram_mock;
    using Lcd = uc1677c::Cgs164a00<Mock>;
    using Segments = Lcd::Segments;
    Lcd lcd;

    auto reset = [&]
    {
        Mock::ram.clear();
        lcd.clear_all();
    };

    CAPTURE(Mock::ram);

    lcd.print(Lcd::CharacterStrings::main, 1);
    lcd.update();
    CHECK(Mock::check_ram({Segments::_17B, Segments::_17C}));

    reset();
    lcd.print(Lcd::CharacterStrings::main, 12);
    lcd.update();
    CHECK(Mock::check_ram({Segments::_16B, Segments::_16C,
                           Segments::_17A, Segments::_17B, Segments::_17G, Segments::_17E, Segments::_17D}));

    reset();
    lcd.print(Lcd::CharacterStrings::main, 123);
    lcd.update();
    CHECK(Mock::check_ram({Segments::_15B, Segments::_15C,
                           Segments::_16A, Segments::_16B, Segments::_16G, Segments::_16E, Segments::_16D,
                           Segments::_17A, Segments::_17B, Segments::_17C, Segments::_17D, Segments::_17G}));

    reset();
    lcd.print(Lcd::CharacterStrings::main, 1234);
    lcd.update();
    CHECK(Mock::check_ram({Segments::_14B, Segments::_14C,
                           Segments::_15A, Segments::_15B, Segments::_15G, Segments::_15E, Segments::_15D,
                           Segments::_16A, Segments::_16B, Segments::_16C, Segments::_16D, Segments::_16G,
                           Segments::_17F, Segments::_17G, Segments::_17B, Segments::_17C}));

    reset();
    lcd.print(Lcd::CharacterStrings::main, 12345);
    lcd.update();
    CHECK(Mock::check_ram({Segments::_13B, Segments::_13C,
                           Segments::_14A, Segments::_14B, Segments::_14G, Segments::_14E, Segments::_14D,
                           Segments::_15A, Segments::_15B, Segments::_15C, Segments::_15D, Segments::_15G,
                           Segments::_16F, Segments::_16G, Segments::_16B, Segments::_16C,
                           Segments::_17A, Segments::_17F, Segments::_17G, Segments::_17C, Segments::_17D}));

    reset();
    lcd.print(Lcd::CharacterStrings::main, 123456);
    lcd.update();
    CHECK(Mock::check_ram({Segments::_12B, Segments::_12C,
                           Segments::_13A, Segments::_13B, Segments::_13G, Segments::_13E, Segments::_13D,
                           Segments::_14A, Segments::_14B, Segments::_14C, Segments::_14D, Segments::_14G,
                           Segments::_15F, Segments::_15G, Segments::_15B, Segments::_15C,
                           Segments::_16A, Segments::_16F, Segments::_16G, Segments::_16C, Segments::_16D,
                           Segments::_17A, Segments::_17F, Segments::_17G, Segments::_17C, Segments::_17D, Segments::_17E}));

    reset();
    lcd.print(Lcd::CharacterStrings::main, 1234567);
    lcd.update();
    CHECK(Mock::check_ram({Segments::_11B, Segments::_11C,
                           Segments::_12A, Segments::_12B, Segments::_12G, Segments::_12E, Segments::_12D,
                           Segments::_13A, Segments::_13B, Segments::_13C, Segments::_13D, Segments::_13G,
                           Segments::_14F, Segments::_14G, Segments::_14B, Segments::_14C,
                           Segments::_15A, Segments::_15F, Segments::_15G, Segments::_15C, Segments::_15D,
                           Segments::_16A, Segments::_16F, Segments::_16G, Segments::_16C, Segments::_16D, Segments::_16E,
                           Segments::_17A, Segments::_17B, Segments::_17C}));

    reset();
    lcd.print(Lcd::CharacterStrings::main, 12345678);
    lcd.update();
    CHECK(Mock::check_ram({Segments::_10B, Segments::_10C,
                           Segments::_11A, Segments::_11B, Segments::_11G, Segments::_11E, Segments::_11D,
                           Segments::_12A, Segments::_12B, Segments::_12C, Segments::_12D, Segments::_12G,
                           Segments::_13F, Segments::_13G, Segments::_13B, Segments::_13C,
                           Segments::_14A, Segments::_14F, Segments::_14G, Segments::_14C, Segments::_14D,
                           Segments::_15A, Segments::_15F, Segments::_15G, Segments::_15C, Segments::_15D, Segments::_15E,
                           Segments::_16A, Segments::_16B, Segments::_16C,
                           Segments::_17A, Segments::_17B, Segments::_17C, Segments::_17D, Segments::_17E, Segments::_17F, Segments::_17G}));

    reset();
    lcd.print(Lcd::CharacterStrings::main, -12345678);
    lcd.update();
    CHECK(Mock::check_ram({Segments::_10B, Segments::_10C,
                           Segments::_11A, Segments::_11B, Segments::_11G, Segments::_11E, Segments::_11D,
                           Segments::_12A, Segments::_12B, Segments::_12C, Segments::_12D, Segments::_12G,
                           Segments::_13F, Segments::_13G, Segments::_13B, Segments::_13C,
                           Segments::_14A, Segments::_14F, Segments::_14G, Segments::_14C, Segments::_14D,
                           Segments::_15A, Segments::_15F, Segments::_15G, Segments::_15C, Segments::_15D, Segments::_15E,
                           Segments::_16A, Segments::_16B, Segments::_16C,
                           Segments::_17A, Segments::_17B, Segments::_17C, Segments::_17D, Segments::_17E, Segments::_17F, Segments::_17G}));

}