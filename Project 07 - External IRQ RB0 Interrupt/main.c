/*
 * External IRQ RB0 Interrupt
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


void __interrupt() ISR(void)
{
    if (INTCONbits.INTF)
    {
        INTCONbits.INTF = 0;
        PORTDbits.RD0 = !PORTDbits.RD0;
    }
}

void main(void)
{
    TRISBbits.TRISB0 = 1;
    TRISD &= 0xFC;
    PORTD &= 0xFC;

    OPTION_REGbits.INTEDG = 1; // Rising edge
    INTCONbits.INTF = 0;
    INTCONbits.INTE = 1;
    INTCONbits.GIE = 1;

    while (1)
    {
        PORTDbits.RD1 = !PORTDbits.RD1;
        __delay_ms(250);
    }
}
