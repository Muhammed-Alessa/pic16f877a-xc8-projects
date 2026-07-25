/*
 * LM35 Digital Thermometer
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

#define LCD_RS PORTDbits.RD0
#define LCD_EN PORTDbits.RD1

static void lcd_pulse(void)
{
    LCD_EN = 1;
    __delay_us(2);
    LCD_EN = 0;
    __delay_us(100);
}

static void lcd_nibble(uint8_t nibble)
{
    PORTD = (PORTD & 0x0FU) | (uint8_t)((nibble & 0x0FU) << 4);
    lcd_pulse();
}

static void lcd_write(uint8_t value, uint8_t rs)
{
    LCD_RS = rs;
    lcd_nibble(value >> 4);
    lcd_nibble(value & 0x0F);
}

static void lcd_cmd(uint8_t cmd)
{
    lcd_write(cmd, 0);
    __delay_ms(2);
}

static void lcd_data(uint8_t data)
{
    lcd_write(data, 1);
}

static void lcd_text(const char *text)
{
    while (*text)
        lcd_data((uint8_t)*text++);
}

static void lcd_uint(uint16_t value)
{
    char digits[6];
    uint8_t i = 0;

    if (value == 0)
    {
        lcd_data('0');
        return;
    }

    while (value > 0 && i < sizeof(digits))
    {
        digits[i++] = (char)('0' + (value % 10U));
        value /= 10U;
    }

    while (i > 0)
        lcd_data((uint8_t)digits[--i]);
}

static void lcd_init(void)
{
    TRISD = 0x00;
    PORTD = 0x00;

    __delay_ms(20);
    LCD_RS = 0;
    LCD_EN = 0;

    lcd_nibble(0x03);
    __delay_ms(5);
    lcd_nibble(0x03);
    __delay_us(150);
    lcd_nibble(0x03);
    lcd_nibble(0x02);

    lcd_cmd(0x28);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
}

static void uart_write_uint(uint16_t value)
{
    char digits[6];
    uint8_t i = 0;

    if (value == 0)
    {
        uart_write('0');
        return;
    }

    while (value > 0 && i < sizeof(digits))
    {
        digits[i++] = (char)('0' + (value % 10U));
        value /= 10U;
    }

    while (i > 0)
        uart_write((uint8_t)digits[--i]);
}

void main(void)
{
    adc_init();
    uart_init();
    lcd_init();

    while (1)
    {
        uint16_t raw = adc_read(0);
        uint32_t millivolts = ((uint32_t)raw * 5000UL) / 1023UL;
        uint16_t temp_c = (uint16_t)(millivolts / 10UL);

        lcd_cmd(0x80);
        lcd_text("Temp: ");
        lcd_uint(temp_c);
        lcd_data(0xDF);
        lcd_data('C');
        lcd_text("   ");

        uart_write_text("Temperature: ");
        uart_write_uint(temp_c);
        uart_write_text(" C\r\n");

        __delay_ms(1000);
    }
}
