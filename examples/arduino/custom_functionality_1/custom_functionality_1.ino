//This example demonstrates adding a custom method to display a network address.

#include "i2c.hpp"
#include "cgs164a00.hpp"

struct NetAddress
{
    uint8_t addr[4];
};

class MyLcd : public uc1677c::Cgs164a00<my_bit_banging::I2C>
{
public:
    void print_net_address(CharacterStrings where, const NetAddress & addr)
    {
        char buf[2];
        uint8_t pos = 0;

        this->clear_string(where);
        for (int i = 0; i < 4; i++)
        {
            _uint8_to_hex(addr.addr[i], buf);
            this->_set_char_in_string(where, this->_get_character(buf[0]), pos++);
            this->_set_char_in_string(where, this->_get_character(buf[1]) | this->_dot, pos++);
        }
    }

private:
    static void _uint8_to_hex(uint8_t value, char * output)
    {
        const char hex_chars[] = "0123456789ABCDEF";
        output[0] = hex_chars[(value >> 4) & 0x0F];
        output[1] = hex_chars[value & 0x0F];
    }
};


MyLcd lcd;

void setup()
{
    my_bit_banging::I2C::init();
    lcd.init();
}

void loop()
{
    lcd.print_net_address(MyLcd::CharacterStrings::main, {192, 168, 0, 1});
    lcd.update();
    delay(2000);

    lcd.print_net_address(MyLcd::CharacterStrings::main, {8, 8, 8, 8});
    lcd.update();
    delay(2000);

    lcd.print_net_address(MyLcd::CharacterStrings::main, {10, 0, 0, 15});
    lcd.update();
    delay(2000);
}
