/*
 * HC-SR04 Ultrasonic Distance Indicator
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


static uint16_t measure_echo_us(void)
{
    uint16_t timeout = 60000;

    PORTBbits.RB1 = 0;
    __delay_us(2);
    PORTBbits.RB1 = 1;
    __delay_us(10);
    PORTBbits.RB1 = 0;

    while (!PORTBbits.RB0 && --timeout)
    {
    }

    if (timeout == 0)
        return 0;

    TMR1H = 0;
    TMR1L = 0;
    T1CONbits.TMR1ON = 1;

    timeout = 60000;
    while (PORTBbits.RB0 && --timeout)
    {
    }

    T1CONbits.TMR1ON = 0;

    if (timeout == 0)
        return 0;

    return ((uint16_t)TMR1H << 8) | TMR1L;
}

void main(void)
{
    ADCON1 = 0x06;

    TRISBbits.TRISB0 = 1;   // Echo
    TRISBbits.TRISB1 = 0;   // Trigger

    TRISD &= 0xF0;
    PORTD &= 0xF0;

    T1CON = 0x00;           // Internal clock, 1:1, initially OFF

    while (1)
    {
        uint16_t echo_us = measure_echo_us();
        uint16_t distance_cm = echo_us / 58U;

        PORTD &= 0xF0;

        if (distance_cm > 0 && distance_cm < 10)
            PORTD |= 0x0F;
        else if (distance_cm < 20)
            PORTD |= 0x07;
        else if (distance_cm < 40)
            PORTD |= 0x03;
        else if (distance_cm < 80)
            PORTD |= 0x01;

        __delay_ms(100);
    }
}
