/*
 * Triangle Waveform Generator - R-2R DAC
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


void main(void)
{
    TRISB = 0x00;
    PORTB = 0x00;

    while (1)
    {
        for (uint16_t sample = 0; sample < 256U; ++sample)
        {
            PORTB = (uint8_t)sample;
            __delay_us(196);
        }

        for (int16_t sample = 254; sample >= 0; --sample)
        {
            PORTB = (uint8_t)sample;
            __delay_us(196);
        }
    }
}
