#include <msp430g2553.h>
#include "cgs164a00.hpp"
#include "../i2c.hpp"

using Lcd = uc1677c::Cgs164a00<my_hal::I2C>;
Lcd lcd;

int main()
{
    WDTCTL = WDTPW + WDTHOLD;

    my_hal::I2C::init();
    lcd.init();
    for(;;)
    {
        lcd.print(Lcd::CharacterStrings::main, 12.f);
        lcd.print(Lcd::CharacterStrings::main, "ewfwf");
        lcd.set_unit(Lcd::Units::kilo | Lcd::Units::amper);
        lcd.update();
    }

    return 0;
}