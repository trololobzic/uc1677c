#include <msp430.h>
#include <stdint.h>
#include "cgs164a00.hpp"
/*
class I2CMaster
{
public:
    // Конструктор инициализирует пины и модуль I2C
    I2CMaster(uint8_t slaveAddress) {
        WDTCTL = WDTPW + WDTHOLD;     // Остановка сторожевого таймера

        // Настройка пинов для MSP430G2553 (P1.6 = SCL, P1.7 = SDA)
        P1SEL  |= BIT6 + BIT7;        // Выбор вторичной функции пинов
        P1SEL2 |= BIT6 + BIT7;

        UCB0CTL1 |= UCSWRST;          // Вход в режим сброса для настройки
        UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC; // Master mode, I2C, Sync
        UCB0CTL1 = UCSSEL_2 + UCSWRST;        // Использовать SMCLK
        UCB0BR0 = 10;                 // Делитель частоты (fSCL = SMCLK/10)
        UCB0BR1 = 0;
        UCB0I2CSA = slaveAddress;     // Адрес ведомого устройства

        UCB0CTL1 &= ~UCSWRST;         // Выход из режима сброса
    }

    // Простая передача одного байта данных
    void transmit(uint8_t data) {
        while (UCB0CTL1 & UCTXSTP);   // Ждем завершения предыдущего STOP

        UCB0CTL1 |= UCTR + UCTXSTT;   // Режим передатчика + START

        while (!(IFG2 & UCB0TXIFG));  // Ждем готовности буфера передачи
        UCB0TXBUF = data;             // Загружаем данные

        while (!(IFG2 & UCB0TXIFG));  // Ждем окончания передачи байта

        UCB0CTL1 |= UCTXSTP;          // Генерируем STOP
        while (UCB0CTL1 & UCTXSTP);   // Ждем подтверждения STOP
    }
};
*/

struct I2C
{
    I2C() = delete;
    ~I2C() = delete;

    static void init()
    {
        P1SEL  |= BIT6 + BIT7;
        P1SEL2 |= BIT6 + BIT7;

        UCB0CTL1 |= UCSWRST;
        UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;
        UCB0CTL1 = UCSSEL_2 + UCSWRST;
        UCB0BR0 = 10;
        UCB0BR1 = 0;
        UCB0CTL1 &= ~UCSWRST;
    }

    static bool start_transmission(uint8_t address)
    {
        while (UCB0CTL1 & UCTXSTP);

        UCB0CTL1 |= UCSWRST;
        UCB0I2CSA = address;
        UCB0CTL1 &= ~UCSWRST;

        UCB0CTL1 |= UCTR + UCTXSTT;
        return true;
    }

    static void end_transmission()
    {
        UCB0CTL1 |= UCTXSTP;
        while (UCB0CTL1 & UCTXSTP);
    }

    static bool write_byte(uint8_t byte)
    {
        while (!(IFG2 & UCB0TXIFG));
        UCB0TXBUF = byte;
        while (UCB0CTL1 & UCTXSTT);
        return !(UCB0STAT & UCNACKIFG);
    }

    static uint8_t read_byte()
    {
        UCB0CTL1 &= ~UCTR;
        UCB0CTL1 |= UCTXSTT;

        while (!(IFG2 & UCB0RXIFG));
        return UCB0RXBUF;
    }
};

using Lcd = uc1677c::Cgs164a00<I2C>;
Lcd lcd;

int main()
{
    WDTCTL = WDTPW + WDTHOLD;

    I2C::init();
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