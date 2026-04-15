# pic16f1939-7segment-lcd-demo
Demo firmware for driving direct 7-segment LCD panels using the internal LCD controller of the PIC16F1939, with Timer1 interrupt-based updates and custom segment mapping.

![LCD Demo](lcd_demo.jpg)

# PIC16F1939 LCD Driver Demo

## Overview

This project demonstrates direct driving of segmented 7-segment LCD displays using the internal LCD controller of the PIC16F1939 microcontroller.

The firmware configures the LCD peripheral, uses Timer1 with an external low-frequency clock source, and updates display contents through an interrupt routine. Custom segment mapping is implemented manually for multiple displayed digits and indicator dots.

## Features

- PIC16F1939 internal LCD driver configuration
- Direct control of segmented LCD display memory registers
- Timer1 interrupt-based display updates
- Manual segment encoding for numeric digits
- Example blinking indicator / decimal point behavior
- Register-level embedded C implementation using XC8

## What the code does

- Configures the LCD peripheral and segment enable registers
- Sets up Timer1 to generate periodic interrupts
- Updates displayed values inside the interrupt service routine
- Maps decimal digits to the correct LCD segment memory bits
- Demonstrates multi-digit display control without an external display driver IC

## Hardware / Environment

- Microcontroller: PIC16F1939
- Toolchain: MPLAB X + XC8
- Display type: direct-drive segmented LCD / 7-segment LCD
- Clocking: external Timer1 oscillator used for timing

## Notes

This project was built as an embedded systems experiment to understand how to use the PIC16F1939 internal LCD peripheral directly instead of relying on an external display driver.

The code is written close to the hardware and focuses on register-level configuration and segment-level control.

## Author

Mert Kaya
