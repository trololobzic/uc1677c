//This example demonstrates adding a custom method to draw running snake.

#include "i2c.hpp"
#include "cgs164a00.hpp"


class MyLcd : public uc1677c::Cgs164a00<my_bit_banging::I2C>
{
public:
    void draw_snake()
    {
        this->clear_string(MyLcd::CharacterStrings::main);
        this->set_segment(_iterator++ % _snake_segments_size, true);
        this->update();
    }

private:
    static constexpr uint32_t _snake_segments_size = 20;
    static const uint8_t _snake_segments[_snake_segments_size];

    uint32_t _iterator = 0;
};

const uint8_t MyLcd::_snake_segments[_snake_segments_size] = {_10A, _11A, _12A, _13A, _14A, _15A, _16A, _17A, _17B, _17C,
                                                              _17D, _16D, _15D, _14D, _13D, _12D, _11D, _10D, _10E, _10F};

MyLcd lcd;

void setup()
{
    my_bit_banging::I2C::init();
    lcd.init();
}

void loop()
{
    lcd.draw_snake();
    delay(200);
}