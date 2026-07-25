/*
 * ADC Potentiometer LED Dimmer
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


static void adc_init(void)
{
    ADCON1 = 0x80;          // Right-justified, Vref=Vdd/Vss
    ADCON0 = 0x41;          // ADC ON, channel AN0, Fosc/8
}

static uint16_t adc_read(uint8_t channel)
{
    if (channel > 7U)
        return 0;

    ADCON0 = (ADCON0 & 0xC5U) | (uint8_t)(channel << 3);
    __delay_us(30);

    ADCON0 |= 0x04U;        // GO/DONE = 1

    while (ADCON0 & 0x04U)
    {
    }

    return ((uint16_t)ADRESH << 8) | ADRESL;
}

static void pwm_init(void)
{
    TRISCbits.TRISC2 = 0;   // CCP1 PWM output
    PR2 = 249;              // ~4 kHz at 4 MHz, prescaler 1
    CCP1CON = 0x0C;         // CCP1 PWM mode
    T2CON = 0x04;           // Timer2 ON, prescaler 1
}

static void pwm_set_10bit(uint16_t duty)
{
    if (duty > 999U)
        duty = 999U;

    CCPR1L = (uint8_t)(duty >> 2);
    CCP1CON = (CCP1CON & 0xCFU) | (uint8_t)((duty & 0x03U) << 4);
}

void main(void)
{
    adc_init();
    pwm_init();

    while (1)
    {
        uint16_t sample = adc_read(0);
        uint16_t duty = (uint16_t)(((uint32_t)sample * 999U) / 1023U);
        pwm_set_10bit(duty);
        __delay_ms(10);
    }
}
