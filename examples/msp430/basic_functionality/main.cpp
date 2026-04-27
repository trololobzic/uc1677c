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
        lcd.light_all_segments(1);
        __delay_cycles(2000);
        lcd.light_all_segments(0);

        lcd.print(Lcd::CharacterStrings::main, "hello");
        lcd.update();
        __delay_cycles(2000);

        lcd.print(Lcd::CharacterStrings::main, 5.12);
        lcd.set_unit(Lcd::Units::volt);
        lcd.update();
        __delay_cycles(2000);

        //lcd.print(Lcd::CharacterStrings::main, 12);
        lcd.set_unit(Lcd::Units::kilo | Lcd::Units::amper);
        lcd.update();
        __delay_cycles(2000);

        lcd.clear_string(Lcd::CharacterStrings::main);
        lcd.print(Lcd::CharacterStrings::additional1, "192.168.1.2");
        lcd.update();
        __delay_cycles(2000);

        lcd.clear_all();
        auto other_segments_mask = lcd.set_other(Lcd::Other::low_battery | Lcd::Other::tariff_word);
        lcd.print(Lcd::CharacterStrings::tariff, 4);
        lcd.update();
        __delay_cycles(2000);

        other_segments_mask |= Lcd::Other::reley;
        lcd.set_other(other_segments_mask);
        lcd.update();
        __delay_cycles(2000);

        other_segments_mask &= ~Lcd::Other::reley;
        lcd.set_other(other_segments_mask);
        lcd.update();
        __delay_cycles(2000);

        lcd.set_other(0);
        lcd.clear_string(Lcd::CharacterStrings::tariff);
        lcd.set_period(Lcd::Period::last | Lcd::Period::year | Lcd::Period::summer);
        lcd.set_tick(Lcd::Tick::tick_1 | Lcd::Tick::tick_3);
        lcd.blink(2);
        lcd.update();
        __delay_cycles(2000);
        lcd.blink(0);
    }

    return 0;
}