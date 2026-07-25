/*
 * CCP1 Compare Mode LED Timer
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


static volatile uint8_t compare_events = 0;

void __interrupt() ISR(void)
{
    if (PIR1bits.CCP1IF)
    {
        PIR1bits.CCP1IF = 0;

        if (++compare_events >= 10)
        {
            compare_events = 0;
            PORTCbits.RC4 = !PORTCbits.RC4;
        }
    }
}

void main(void)
{
    TRISCbits.TRISC4 = 0;
    PORTCbits.RC4 = 0;

    TMR1H = 0;
    TMR1L = 0;
    T1CON = 0x01;          // Timer1 internal clock, ON

    // 50,000 ticks x 1 us = 50 ms.
    CCPR1H = (uint8_t)(50000U >> 8);
    CCPR1L = (uint8_t)50000U;

    CCP1CON = 0x0B;        // Compare special-event trigger: resets Timer1
    PIR1bits.CCP1IF = 0;
    PIE1bits.CCP1IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;

    while (1)
    {
    }
}
