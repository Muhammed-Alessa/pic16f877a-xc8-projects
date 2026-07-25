/*
 * DC Motor Speed and Direction - L293D
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

static uint16_t duty = 400;

static void motor_forward(void)
{
    PORTDbits.RD0 = 1;
    PORTDbits.RD1 = 0;
}

static void motor_reverse(void)
{
    PORTDbits.RD0 = 0;
    PORTDbits.RD1 = 1;
}

static void motor_stop(void)
{
    PORTDbits.RD0 = 0;
    PORTDbits.RD1 = 0;
    pwm_set_10bit(0);
}

void main(void)
{
    ADCON1 = 0x06;

    TRISD &= 0xFC;          // RD0/RD1 direction outputs
    TRISB |= 0x0F;          // RB0-RB3 buttons
    OPTION_REGbits.nRBPU = 0;

    pwm_init();
    motor_forward();
    pwm_set_10bit(duty);

    while (1)
    {
        if (!PORTBbits.RB0)
        {
            if (duty <= 899U) duty += 100U;
            pwm_set_10bit(duty);
            __delay_ms(180);
        }

        if (!PORTBbits.RB1)
        {
            if (duty >= 100U) duty -= 100U;
            pwm_set_10bit(duty);
            __delay_ms(180);
        }

        if (!PORTBbits.RB2)
        {
            motor_reverse();
            pwm_set_10bit(duty);
            __delay_ms(180);
        }

        if (!PORTBbits.RB3)
        {
            motor_stop();
            __delay_ms(180);
        }
    }
}
