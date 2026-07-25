/*
 * HC-05 Bluetooth LED Control
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


static void uart_init(void)
{
    // 9600 baud at 4 MHz with BRGH=1 -> SPBRG=25.
    SPBRG = 25;
    TXSTA = 0x24;           // BRGH=1, TXEN=1, async mode
    RCSTA = 0x90;           // SPEN=1, CREN=1
}

static void uart_write(uint8_t data)
{
    while (!PIR1bits.TXIF)
    {
    }
    TXREG = data;
}

static uint8_t uart_read(void)
{
    if (RCSTAbits.OERR)
    {
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }

    while (!PIR1bits.RCIF)
    {
    }

    return RCREG;
}

static void uart_write_text(const char *text)
{
    while (*text)
        uart_write((uint8_t)*text++);
}

void main(void)
{
    uart_init();

    TRISD = 0x00;
    PORTD = 0x00;

    while (1)
    {
        uint8_t command = uart_read();

        if (command >= '0' && command <= '7')
            PORTD ^= (uint8_t)(1U << (command - '0'));
        else if (command == 'A')
            PORTD = 0xFF;
        else if (command == 'X')
            PORTD = 0x00;
    }
}
