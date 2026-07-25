/*
 * Timer1 External Pulse Counter
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
    TRISCbits.TRISC0 = 1;   // RC0/T1CKI external counter input
    TRISD = 0x00;
    PORTD = 0x00;

    TMR1H = 0;
    TMR1L = 0;

    // Timer1 ON, external clock, synchronized, 1:1 prescaler.
    T1CON = 0x03;

    while (1)
    {
        PORTD = TMR1L;
    }
}
