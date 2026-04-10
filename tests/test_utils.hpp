#pragma once

#include <cstdint>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include "uc1677c.hpp"

namespace doctest
{

template <typename T>
struct StringMaker<std::vector<T>>
{
    static String convert(const std::vector<T>& vec)
    {
        std::ostringstream oss;
        oss << "[";
        std::ranges::for_each(vec, [&](const auto & byte){
            oss << std::hex << std::setfill('0') << std::setw(2) << static_cast<size_t>(byte) << " ";
        });
        oss << "]";
        return oss.str().c_str();
    }
};

}

namespace uc1677c::tests
{

struct I2C_ram_mock
{
    static bool start_transmission(uint8_t)
    {
        frame.clear();
        return true;
    }

    static void end_transmission()
    {
        if (frame.size() == 2 && frame[0] == 0x40)
        {
            ram.push_back(frame[1]);
        }
    }

    static bool write_byte(uint8_t data)
    {
        frame.push_back(data);
        return true;
    }

    static uint8_t read_byte()
    {
        return 0;
    }

    static bool check_ram(const std::vector<size_t> & bits)
    try
    {
        std::decay_t<decltype(ram)> expected(ram.size(), 0);
        std::ranges::for_each(bits, [&](const auto & bit){
            const auto byte_idx = bit / 8;
            if (byte_idx > expected.size())
            {
                throw std::exception();
            }
            expected[byte_idx] |= 0x80 >> (bit % 8);
        });
        return ram == expected;
    }
    catch(std::exception &)
    {
        return false;
    }

    static inline std::vector<uint8_t> ram;
    static inline std::vector<uint8_t> frame;
};

}