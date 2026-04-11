#pragma once

#include <msp430g2553.h>

namespace my_hal
{

struct I2C
{
    I2C() = delete;
    ~I2C() = delete;

    static void init()
    {
        P1SEL  |= BIT6 | BIT7;
        P1SEL2 |= BIT6 | BIT7;

        UCB0CTL1 |= UCSWRST;
        UCB0CTL0 = UCMST | UCMODE_3 | UCSYNC;
        UCB0CTL1 = UCSSEL_2 | UCSWRST;
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

        UCB0CTL1 |= UCTR | UCTXSTT;
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

}