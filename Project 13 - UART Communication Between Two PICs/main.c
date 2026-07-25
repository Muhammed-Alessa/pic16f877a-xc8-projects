/*
 * UART Communication Between Two PICs
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


#define UART_ROLE_MASTER 1

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

#if UART_ROLE_MASTER
    ADCON1 = 0x06;
    TRISB |= 0x07;
    OPTION_REGbits.nRBPU = 0;
    TRISD = 0x00;

    uint8_t value = 0;
    PORTD = value;

    while (1)
    {
        if (!PORTBbits.RB0)
        {
            ++value;
            PORTD = value;
            __delay_ms(180);
        }

        if (!PORTBbits.RB1)
        {
            --value;
            PORTD = value;
            __delay_ms(180);
        }

        if (!PORTBbits.RB2)
        {
            uart_write(value);
            __delay_ms(180);
        }
    }
#else
    TRISD = 0x00;

    while (1)
    {
        PORTD = uart_read();
    }
#endif
}
