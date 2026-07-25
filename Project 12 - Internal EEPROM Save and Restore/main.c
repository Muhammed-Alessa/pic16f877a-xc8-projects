/*
 * Internal EEPROM Save and Restore
 * MCU: PIC16F877A
 * Toolchain: MPLAB X + XC8
 * Clock: 4 MHz crystal
 *
 * Independently rewritten study project based on the practical LAB sequence
 * in Khaled Magdy's PIC microcontroller course.
 */

// PIC16F877A configuration bits
#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 4000000UL


static uint8_t eeprom_read(uint8_t address)
{
    EEADR = address;
    EECON1bits.EEPGD = 0;
    EECON1bits.RD = 1;
    return EEDATA;
}

static void eeprom_write(uint8_t address, uint8_t data)
{
    while (EECON1bits.WR)
    {
    }

    EEADR = address;
    EEDATA = data;
    EECON1bits.EEPGD = 0;
    EECON1bits.WREN = 1;

    uint8_t gie_state = INTCONbits.GIE;
    INTCONbits.GIE = 0;

    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;

    INTCONbits.GIE = gie_state;

    while (EECON1bits.WR)
    {
    }

    EECON1bits.WREN = 0;
}

void main(void)
{
    ADCON1 = 0x06;

    TRISD &= 0xF8;
    TRISB |= 0x03;
    OPTION_REGbits.nRBPU = 0;

    uint8_t value = eeprom_read(0) & 0x07;
    PORTD = (PORTD & 0xF8) | value;

    while (1)
    {
        if (!PORTBbits.RB0)
        {
            value = (value + 1U) & 0x07U;
            PORTD = (PORTD & 0xF8) | value;
            eeprom_write(0, value);
            __delay_ms(200);
        }

        if (!PORTBbits.RB1)
        {
            value = eeprom_read(0) & 0x07U;
            PORTD = (PORTD & 0xF8) | value;
            __delay_ms(200);
        }
    }
}
