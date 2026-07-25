/*
 * CCP1 Capture Mode
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


static volatile uint8_t captured = 0;

void __interrupt() ISR(void)
{
    if (PIR1bits.CCP1IF)
    {
        PIR1bits.CCP1IF = 0;
        captured = CCPR1L;
        PORTB = captured;
    }
}

void main(void)
{
    TRISB = 0x00;           // Captured value display
    TRISD = 0x00;           // Live Timer1 low byte display
    PORTB = 0x00;
    PORTD = 0x00;

    TRISCbits.TRISC0 = 1;   // T1CKI
    TRISCbits.TRISC2 = 1;   // CCP1 capture input

    TMR1H = 0;
    TMR1L = 0;
    T1CON = 0x03;           // Counter mode, synchronized, ON

    CCP1CON = 0x05;         // Capture every rising edge
    PIR1bits.CCP1IF = 0;
    PIE1bits.CCP1IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;

    while (1)
    {
        PORTD = TMR1L;
    }
}
