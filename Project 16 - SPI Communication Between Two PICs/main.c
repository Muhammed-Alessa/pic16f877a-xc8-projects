/*
 * SPI Communication Between Two PICs
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


#define SPI_ROLE_MASTER 1

static void spi_init(void)
{
#if SPI_ROLE_MASTER
    TRISCbits.TRISC3 = 0;   // SCK output
    TRISCbits.TRISC4 = 1;   // SDI input
    TRISCbits.TRISC5 = 0;   // SDO output
    SSPSTAT = 0x40;         // CKE=1
    SSPCON = 0x20;          // SSPEN=1, master Fosc/4
#else
    TRISCbits.TRISC3 = 1;   // SCK input
    TRISCbits.TRISC4 = 1;   // SDI input
    TRISCbits.TRISC5 = 0;   // SDO output
    SSPSTAT = 0x40;
    SSPCON = 0x25;          // SSPEN=1, slave mode, SS disabled
#endif
}

static uint8_t spi_transfer(uint8_t data)
{
    SSPBUF = data;

    while (!SSPSTATbits.BF)
    {
    }

    return SSPBUF;
}

void main(void)
{
    spi_init();

#if SPI_ROLE_MASTER
    uint8_t value = 0;

    while (1)
    {
        (void)spi_transfer(value++);
        __delay_ms(250);
    }
#else
    TRISD = 0x00;
    PORTD = 0x00;

    while (1)
    {
        if (SSPSTATbits.BF)
            PORTD = SSPBUF;
    }
#endif
}
