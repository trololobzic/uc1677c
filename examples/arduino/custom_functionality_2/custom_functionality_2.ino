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

const uint8_t MyLcd::_snake_segments[_snake_segments_size] = {MyLcd::Segments::_10A, MyLcd::Segments::_11A, MyLcd::Segments::_12A, MyLcd::Segments::_13A,
                                                              MyLcd::Segments::_14A, MyLcd::Segments::_15A, MyLcd::Segments::_16A, MyLcd::Segments::_17A,
                                                              MyLcd::Segments::_17B, MyLcd::Segments::_17C, MyLcd::Segments::_17D, MyLcd::Segments::_16D,
                                                              MyLcd::Segments::_15D, MyLcd::Segments::_14D, MyLcd::Segments::_13D, MyLcd::Segments::_12D,
                                                              MyLcd::Segments::_11D, MyLcd::Segments::_10D, MyLcd::Segments::_10E, MyLcd::Segments::_10F};

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