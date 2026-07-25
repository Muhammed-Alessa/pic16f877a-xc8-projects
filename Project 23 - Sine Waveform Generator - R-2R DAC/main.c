/*
 * Sine Waveform Generator - R-2R DAC
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


static const uint8_t sine_table[32] =
{
    128, 152, 176, 198, 218, 234, 245, 253,
    255, 253, 245, 234, 218, 198, 176, 152,
    128, 103,  79,  57,  37,  21,  10,   2,
      0,   2,  10,  21,  37,  57,  79, 103
};

void main(void)
{
    TRISB = 0x00;
    PORTB = 0x00;

    uint8_t index = 0;

    while (1)
    {
        PORTB = sine_table[index++];

        if (index >= 32U)
            index = 0;

        __delay_us(625);
    }
}
