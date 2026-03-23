#pragma once

namespace my_bit_banging
{

class I2C
{
    static constexpr int SDA = 6;
    static constexpr int SCL = 5;

public:
    static void init()
    {
        _sda_dir(1);
        _scl_dir(1);
        delay(200);
    }

    static bool start_transmission(uint8_t addr)
    {
        _scl_set(1);
        _sda_set(1);
        _sda_set(0);
        _scl_set(0);

        return write_byte(addr);
    }

    static void end_transmission()
    {
        _sda_set(0);
        _scl_set(1);
        _sda_set(1);
    }

    static bool write_byte(uint8_t byte)
    {
        bool result = false;
        _scl_set(0);
        for (int i = 0; i < 8; i++)
        {
            _sda_set(byte & 0x80 ? 1 : 0);
            byte <<= 1;

            _scl_set(1);

            _nop();
            _nop();
            _nop();
            _nop();

            _scl_set(0);
            _sda_set(1);
        }
        _scl_set(1);

        //wait ack
        _sda_dir(0);

        for (int i = 0; i < 50; i++)
        {
            if (_sda_get())
            {
                result = true;
                break;
            }
        }

        _sda_dir(1);
        _scl_set(0);

        return result;
    }

    static uint8_t read_byte()
    {
        uint8_t result = 0;

        _sda_dir(0);
        for (int i = 8 ; i > 0 ; i--)
        {
            _scl_set(0);
            result |= _sda_get() << (i-1);
            _scl_set(1);
        }
        _sda_dir(1);
        _scl_set(0);

        return result;
    }

private:
    static void _scl_dir(uint8_t dir)
    {
        pinMode(SCL, dir);
    }

    static void _sda_dir(uint8_t dir)
    {
        pinMode(SDA, dir);
    }

    static void _scl_set(uint8_t val)
    {
        digitalWrite(SCL , val);
    }

    static void _sda_set(uint8_t val)
    {
        digitalWrite(SDA , val);
    }

    static uint8_t _sda_get()
    {
        return digitalRead(SDA);
    }

    static void _nop()
    {
        __asm__ __volatile__ ("nop\n\t");
    }
};

}