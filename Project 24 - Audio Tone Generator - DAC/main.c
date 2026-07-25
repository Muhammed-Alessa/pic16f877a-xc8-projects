/*
 * Audio Tone Generator - DAC
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


static const uint8_t tone_wave[16] =
{
    128, 176, 218, 245, 255, 245, 218, 176,
    128,  79,  37,  10,   0,  10,  37,  79
};

static void play_cycle(uint16_t delay_us)
{
    for (uint8_t i = 0; i < 16; ++i)
    {
        PORTD = tone_wave[i];

        for (uint16_t us = 0; us < delay_us; ++us)
            __delay_us(1);
    }
}

void main(void)
{
    ADCON1 = 0x06;

    TRISD = 0x00;           // 8-bit DAC data
    TRISB |= 0x0F;          // Four buttons
    OPTION_REGbits.nRBPU = 0;

    while (1)
    {
        if (!PORTBbits.RB0)
            play_cycle(313);   // approximately 200 Hz

        else if (!PORTBbits.RB1)
            play_cycle(125);   // approximately 500 Hz

        else if (!PORTBbits.RB2)
            play_cycle(63);    // approximately 1 kHz

        else if (!PORTBbits.RB3)
            play_cycle(44);    // approximately 1.4 kHz

        else
            PORTD = 128;
    }
}
