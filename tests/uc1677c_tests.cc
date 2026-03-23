#include <cstdint>
#include <vector>

#include "doctest/doctest.h"
#include "uc1677c.hpp"

namespace uc1677c::test
{

struct I2C_mock
{
    static bool start_transmission(uint8_t addr)
    {
        start_called = true;
        end_called = false;
        last_addr = addr;
        written_bytes.push_back(addr);
        return true;
    }

    static void end_transmission()
    {
        end_called = true;
    }

    static bool write_byte(uint8_t data)
    {
        if (start_called && !end_called)
        {
            written_bytes.push_back(data);
        }
        return true;
    }

    static uint8_t read_byte()
    {
        return 0;
    }

    static void reset()
    {
        written_bytes.clear();
        start_called = end_called = false;
        last_addr = 0;
    }

    static bool check_transmission(const std::vector<uint8_t> & reference_value)
    {
        return start_called && end_called && reference_value == written_bytes;
    }

    static inline uint8_t last_addr = 0;
    static inline bool start_called = false;
    static inline bool end_called = false;
    static inline std::vector<uint8_t> written_bytes;
};

}

TEST_CASE("uc1677c initialisation")
{
    uc1677c::Uc1677cBase<uc1677c::test::I2C_mock, 2> lcd;

    SUBCASE("with bump control")
    {
        uc1677c::test::I2C_mock::reset();
        CHECK(lcd.init(true));
        CHECK(uc1677c::test::I2C_mock::check_transmission({0x70, 0x00, 0x12,
                                                        0x70, 0x00, 0xfe,
                                                        0x70, 0x00, 0xe0,
                                                        0x70, 0x00, 0xbf,
                                                        0x70, 0x00, 0xaa,
                                                        0x70, 0x00, 0xd4,
                                                        0x70, 0x00, 0xc0,
                                                        0x70, 0x00, 0x11,
                                                        0x70, 0x00, 0x35,
                                                        0x70, 0x00, 0x14,
                                                        0x70, 0x00, 0xce,
                                                        0x70, 0x00, 0x1c,
                                                        0x70, 0x00, 0x51}));
    }

    SUBCASE("without bump control")
    {
        uc1677c::test::I2C_mock::reset();
        CHECK(lcd.init(false));
        CHECK(uc1677c::test::I2C_mock::check_transmission({0x70, 0x00, 0x12,
                                                        0x70, 0x00, 0xfe,
                                                        0x70, 0x00, 0xe0,
                                                        0x70, 0x00, 0xb0,
                                                        0x70, 0x00, 0xaa,
                                                        0x70, 0x00, 0xd4,
                                                        0x70, 0x00, 0xc0,
                                                        0x70, 0x00, 0x11,
                                                        0x70, 0x00, 0x35,
                                                        0x70, 0x00, 0x14,
                                                        0x70, 0x00, 0xce,
                                                        0x70, 0x00, 0x1c,
                                                        0x70, 0x00, 0x51}));
    }
}

TEST_CASE("uc1677c setting segment")
{
    uc1677c::Uc1677cBase<uc1677c::test::I2C_mock, 2> lcd;

    auto check_ram = [](uint8_t first_byte, uint8_t second_byte)
    {
        REQUIRE(uc1677c::test::I2C_mock::written_bytes.size() == 12);
        CHECK(uc1677c::test::I2C_mock::written_bytes[0] == 0x70);
        CHECK(uc1677c::test::I2C_mock::written_bytes[1] == 0x00);
        CHECK(uc1677c::test::I2C_mock::written_bytes[2] == 0x02);

        CHECK(uc1677c::test::I2C_mock::written_bytes[3] == 0x70);
        CHECK(uc1677c::test::I2C_mock::written_bytes[4] == 0x00);
        CHECK(uc1677c::test::I2C_mock::written_bytes[5] == 0x48);

        CHECK(uc1677c::test::I2C_mock::written_bytes[6] == 0x70);
        CHECK(uc1677c::test::I2C_mock::written_bytes[7] == 0x40);
        CHECK(uc1677c::test::I2C_mock::written_bytes[8] == first_byte);

        CHECK(uc1677c::test::I2C_mock::written_bytes[9] == 0x70);
        CHECK(uc1677c::test::I2C_mock::written_bytes[10] == 0x40);
        CHECK(uc1677c::test::I2C_mock::written_bytes[11] == second_byte);
        uc1677c::test::I2C_mock::reset();
    };

    uc1677c::test::I2C_mock::reset();
    CHECK(lcd.set_segment(0, true));
    CHECK(lcd.update());
    check_ram(0x80, 0x00);

    CHECK(lcd.set_segment(1, true));
    CHECK(lcd.set_segment(2, true));
    CHECK(lcd.set_segment(3, true));
    CHECK(lcd.update());
    check_ram(0xF0, 0x00);

    CHECK(lcd.set_segment(4, true));
    CHECK(lcd.set_segment(5, true));
    CHECK(lcd.set_segment(6, true));
    CHECK(lcd.update());
    check_ram(0xFE, 0x00);

    CHECK(lcd.set_segment(7, true));
    CHECK(lcd.update());
    check_ram(0xFF, 0x00);

    CHECK(lcd.set_segment(8, true));
    CHECK(lcd.set_segment(9, true));
    CHECK(lcd.set_segment(10, true));
    CHECK(lcd.update());
    check_ram(0xFF, 0xE0);

    CHECK(lcd.set_segment(11, true));
    CHECK(lcd.set_segment(12, true));
    CHECK(lcd.set_segment(13, true));
    CHECK(lcd.set_segment(14, true));
    CHECK(lcd.update());
    check_ram(0xFF, 0xFE);

    CHECK(lcd.set_segment(15, true));
    CHECK(lcd.update());
    check_ram(0xFF, 0xFF);

    CHECK(lcd.set_segment(0, false));
    CHECK(lcd.update());
    check_ram(0x7F, 0xFF);

    CHECK(lcd.set_segment(8, false));
    CHECK(lcd.update());
    check_ram(0x7F, 0x7F);

    lcd.clear_all();
    CHECK(lcd.update());
    check_ram(0x00, 0x00);
}

TEST_CASE("uc1677c setting all segments")
{
    uc1677c::Uc1677cBase<uc1677c::test::I2C_mock, 2> lcd;

    SUBCASE("on")
    {
        uc1677c::test::I2C_mock::reset();
        CHECK(lcd.light_all_segments(true));
        CHECK(uc1677c::test::I2C_mock::check_transmission({0x70, 0x00, 0x16}));
    }

    SUBCASE("off")
    {
        uc1677c::test::I2C_mock::reset();
        CHECK(lcd.light_all_segments(false));
        CHECK(uc1677c::test::I2C_mock::check_transmission({0x70, 0x00, 0x14}));
    }
}

TEST_CASE("uc1677c blink")
{
    uc1677c::Uc1677cBase<uc1677c::test::I2C_mock, 2> lcd;

    uc1677c::test::I2C_mock::reset();
    CHECK(lcd.blink(0));
    CHECK(uc1677c::test::I2C_mock::check_transmission({0x70, 0x00, 0xf0}));

    uc1677c::test::I2C_mock::reset();
    CHECK(lcd.blink(1));
    CHECK(uc1677c::test::I2C_mock::check_transmission({0x70, 0x00, 0xf1}));

    uc1677c::test::I2C_mock::reset();
    CHECK(lcd.blink(2));
    CHECK(uc1677c::test::I2C_mock::check_transmission({0x70, 0x00, 0xf2}));

    uc1677c::test::I2C_mock::reset();
    CHECK(lcd.blink(3));
    CHECK(uc1677c::test::I2C_mock::check_transmission({0x70, 0x00, 0xf3}));

    uc1677c::test::I2C_mock::reset();
    CHECK_FALSE(lcd.blink(4));
    CHECK_FALSE(uc1677c::test::I2C_mock::check_transmission({}));
}

TEST_CASE("uc1677c utils")
{
    SUBCASE("number_of_bytes")
    {
        CHECK(uc1677c::Utils::number_of_bytes(0) == 0);
        CHECK(uc1677c::Utils::number_of_bytes(8) == 1);
        CHECK(uc1677c::Utils::number_of_bytes(9) == 2);
        CHECK(uc1677c::Utils::number_of_bytes(10) == 2);
        CHECK(uc1677c::Utils::number_of_bytes(16) == 2);
        CHECK(uc1677c::Utils::number_of_bytes(17) == 3);
    }

    SUBCASE("absolute_value")
    {
        int a = 0;
        CHECK(uc1677c::Utils::absolute_value(a) == ' ');
        CHECK(a == 0);

        a = 10;
        CHECK(uc1677c::Utils::absolute_value(a) == ' ');
        CHECK(a == 10);

        a = 9999;
        CHECK(uc1677c::Utils::absolute_value(a) == ' ');
        CHECK(a == 9999);

        a = -10;
        CHECK(uc1677c::Utils::absolute_value(a) == '-');
        CHECK(a == 10);

        a = -999;
        CHECK(uc1677c::Utils::absolute_value(a) == '-');
        CHECK(a == 999);
    }

    SUBCASE("power_of_10")
    {
        CHECK(uc1677c::Utils::power_of_10(0) == 1);
        CHECK(uc1677c::Utils::power_of_10(1) == 10);
        CHECK(uc1677c::Utils::power_of_10(2) == 100);
        CHECK(uc1677c::Utils::power_of_10(3) == 1000);
        CHECK(uc1677c::Utils::power_of_10(4) == 10000);
        CHECK(uc1677c::Utils::power_of_10(5) == 100000);
    }
}