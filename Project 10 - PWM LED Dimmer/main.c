/*
 * PWM LED Dimmer
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


static void pwm_init(void)
{
    TRISCbits.TRISC2 = 0;   // CCP1 PWM output
    PR2 = 249;              // ~4 kHz at 4 MHz, prescaler 1
    CCP1CON = 0x0C;         // CCP1 PWM mode
    T2CON = 0x04;           // Timer2 ON, prescaler 1
}

static void pwm_set_10bit(uint16_t duty)
{
    if (duty > 999U)
        duty = 999U;

    CCPR1L = (uint8_t)(duty >> 2);
    CCP1CON = (CCP1CON & 0xCFU) | (uint8_t)((duty & 0x03U) << 4);
}

void main(void)
{
    pwm_init();

    while (1)
    {
        for (uint16_t duty = 0; duty <= 999; duty += 10)
        {
            pwm_set_10bit(duty);
            __delay_ms(10);
        }

        for (int16_t duty = 999; duty >= 0; duty -= 10)
        {
            pwm_set_10bit((uint16_t)duty);
            __delay_ms(10);
        }
    }
}
