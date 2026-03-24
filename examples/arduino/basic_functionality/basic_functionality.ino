#include "i2c.hpp"
#include "cgs164a00.hpp"
#include "cgs214a06.hpp"

using Lcd = uc1677c::Cgs214a06<my_bit_banging::I2C>;
Lcd lcd;

void setup()
{
    my_bit_banging::I2C::init();
    lcd.init();
}

void loop()
{
    lcd.print(Lcd::CharacterStrings::main, "sefesf");
    lcd.print(Lcd::CharacterStrings::main, 12.f);
    lcd.set_unit(Lcd::Units::kilo | Lcd::Units::amper);
    lcd.update();
}
