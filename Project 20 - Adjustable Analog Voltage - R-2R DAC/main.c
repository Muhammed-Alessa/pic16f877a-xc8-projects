/*
 * Adjustable Analog Voltage - R-2R DAC
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


static void adc_init(void)
{
    ADCON1 = 0x80;          // Right-justified, Vref=Vdd/Vss
    ADCON0 = 0x41;          // ADC ON, channel AN0, Fosc/8
}

static uint16_t adc_read(uint8_t channel)
{
    if (channel > 7U)
        return 0;

    ADCON0 = (ADCON0 & 0xC5U) | (uint8_t)(channel << 3);
    __delay_us(30);

    ADCON0 |= 0x04U;        // GO/DONE = 1

    while (ADCON0 & 0x04U)
    {
    }

    return ((uint16_t)ADRESH << 8) | ADRESL;
}

void main(void)
{
    adc_init();

    TRISB = 0x00;
    PORTB = 0x00;

    while (1)
    {
        uint16_t raw = adc_read(0);
        PORTB = (uint8_t)(raw >> 2);
    }
}
