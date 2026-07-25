/*
 * Timer1 One-Second LED Blink
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


static volatile uint8_t ticks = 0;

static void timer1_reload(void)
{
    // 4 MHz -> instruction clock = 1 MHz -> 1 us per Timer1 tick.
    // 65536 - 62500 = 3036 = 0x0BDC.
    TMR1H = 0x0B;
    TMR1L = 0xDC;
}

void __interrupt() ISR(void)
{
    if (PIR1bits.TMR1IF)
    {
        PIR1bits.TMR1IF = 0;
        timer1_reload();

        if (++ticks >= 16)
        {
            ticks = 0;
            PORTBbits.RB0 = !PORTBbits.RB0;
        }
    }
}

void main(void)
{
    TRISBbits.TRISB0 = 0;
    PORTBbits.RB0 = 0;

    T1CON = 0x01;           // Timer1 ON, internal clock, 1:1 prescaler
    timer1_reload();

    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;

    while (1)
    {
        // Timing is handled by Timer1.
    }
}
