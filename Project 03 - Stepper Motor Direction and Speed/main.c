/*
 * Stepper Motor Direction and Speed
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


static const uint8_t sequence[4] = {0x01, 0x02, 0x04, 0x08};

static void step_forward(uint16_t steps, uint16_t delay_ms)
{
    for (uint16_t s = 0; s < steps; ++s)
    {
        PORTB = (PORTB & 0xF0) | sequence[s & 0x03];

        for (uint16_t ms = 0; ms < delay_ms; ++ms)
            __delay_ms(1);
    }
}

static void step_reverse(uint16_t steps)
{
    for (uint16_t s = 0; s < steps; ++s)
    {
        PORTB = (PORTB & 0xF0) | sequence[3 - (s & 0x03)];
        __delay_ms(5);
    }
}

void main(void)
{
    TRISB &= 0xF0;
    PORTB &= 0xF0;

    while (1)
    {
        step_forward(200, 5);
        __delay_ms(500);
        step_reverse(200);
        __delay_ms(500);
    }
}
