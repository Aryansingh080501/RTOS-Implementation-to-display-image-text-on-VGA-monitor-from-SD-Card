RTOS, SD Card, and VGA Implementation on Embedded System
This project demonstrates an embedded system design using the Nios II processor on the DE2-115 FPGA board, interfacing with an SD card and VGA monitor through I2C and SPI communication protocols. The system is programmed in C and runs on a Real-Time Operating System (RTOS) environment.

Project Overview
This project aims to integrate various components on an FPGA-based embedded system to:

Enable data storage and retrieval on an SD card using SPI.
Display graphical outputs on a VGA monitor.
Manage tasks efficiently using an RTOS, ensuring real-time performance and task scheduling.
Tools and Environment
Quartus for FPGA synthesis and design.
Qsys for system integration on the FPGA.
Eclipse IDE with Nios II software build tools for embedded C programming.
DE2-115 FPGA Board with onboard Nios II processor.
Key Components
1. RTOS Integration
The RTOS manages concurrent tasks, enabling data processing from the SD card and graphical rendering on the VGA display.
It schedules tasks, handles timing, and prioritizes critical operations for reliable real-time performance.
2. SD Card Interface (SPI Protocol)
The system uses the SPI (Serial Peripheral Interface) to read from and write to an SD card.
Data stored on the SD card can include graphics or text, which are processed and displayed on the VGA monitor.
3. VGA Display (I2C Protocol)
A VGA controller is used to render graphical output on a connected monitor.
The display configuration, handled through I2C, includes setting resolution, color depth, and refresh rates for seamless display integration.
