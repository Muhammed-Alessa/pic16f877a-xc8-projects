# LM35 Digital Thermometer

## Description
Reads an LM35 through AN0, converts the ADC result to degrees Celsius, displays it on a 16x2 LCD, and also sends the value over UART.

## Hardware
- PIC16F877A
- PICkit 3
- 4 MHz crystal
- LM35 temperature sensor
- 16x2 HD44780-compatible LCD
- 10 kohm contrast potentiometer
- USB-TTL converter (optional)
- Breadboard and jumper wires

## Code
See [main.c](main.c).

## Circuit
![Breadboard](images/breadboard.jpg)
