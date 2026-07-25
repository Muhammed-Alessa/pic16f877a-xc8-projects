/*
 * Blinking LED - GPIO LAB
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
    ADCON1 = 0x06;          // Make PORTA pins digital where applicable
    TRISBbits.TRISB0 = 0;   // RB0 output
    PORTBbits.RB0 = 0;

    while (1)
    {
        PORTBbits.RB0 = !PORTBbits.RB0;
        __delay_ms(500);
    }
}
