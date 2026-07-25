# PIC16F877A XC8 Projects

A GitHub portfolio built from the practical LAB/project sequence of Khaled Magdy's **Embedded Systems Course - PIC Microcontrollers Tutorials [Arabic]**.

Target setup:

- **MCU:** PIC16F877A
- **IDE:** MPLAB X
- **Compiler:** XC8
- **Programmer:** PICkit 3
- **Clock used by these projects:** 4 MHz external crystal

The descriptions and source files here are independently rewritten for this repository. They are not copied from the course.

## Repository Structure

```text
Project XX - Project Name/
├── main.c
├── README.md
└── images/
    └── .gitkeep
```

After rebuilding a project on real hardware, add your own photo as:

```text
images/breadboard.jpg
```

## Projects

- `Project 01 - Blinking LED - GPIO LAB`
- `Project 02 - 7-Segment Decimal Counter`
- `Project 03 - Stepper Motor Direction and Speed`
- `Project 04 - Timer1 One-Second LED Blink`
- `Project 05 - HC-SR04 Ultrasonic Distance Indicator`
- `Project 06 - Timer1 External Pulse Counter`
- `Project 07 - External IRQ RB0 Interrupt`
- `Project 08 - CCP1 Capture Mode`
- `Project 09 - CCP1 Compare Mode LED Timer`
- `Project 10 - PWM LED Dimmer`
- `Project 11 - DC Motor Speed and Direction - L293D`
- `Project 12 - Internal EEPROM Save and Restore`
- `Project 13 - UART Communication Between Two PICs`
- `Project 14 - HC-05 Bluetooth LED Control`
- `Project 15 - USB-TTL PC Serial Control`
- `Project 16 - SPI Communication Between Two PICs`
- `Project 17 - ADC Potentiometer LED Dimmer`
- `Project 18 - Finger Snap Switch`
- `Project 19 - LM35 Digital Thermometer`
- `Project 20 - Adjustable Analog Voltage - R-2R DAC`
- `Project 21 - Sawtooth Waveform Generator - R-2R DAC`
- `Project 22 - Triangle Waveform Generator - R-2R DAC`
- `Project 23 - Sine Waveform Generator - R-2R DAC`
- `Project 24 - Audio Tone Generator - DAC`

## Notes

- The repository focuses on the **practical LABs and interfacing projects** from the playlist rather than creating folders for purely theoretical lessons.
- PIC16F877A configuration bits are kept directly inside each `main.c` to preserve the simple two-file-per-project style.
- The ADC/DAC portion follows the later lessons in the same playlist. Because PIC16F877A has no internal DAC module, the DAC projects use an external **8-bit R-2R resistor ladder**, matching the course concept.
- The UART and SPI two-MCU projects use one `main.c` with a compile-time role setting so the project folder stays simple.
- No course circuit images are included. Add your own Proteus screenshot or, preferably, your own real breadboard photo after testing.
