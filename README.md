# RC-CAR-ASA-
RC Car design, Control System, and Documentation

## Overview
This projects demonstrate the design and implementation of a microcontroller based platform integrating embedded firmware, motor control, and wireless communication. The system was developed following basic embedded systems engineering practices, including modular firmware design, hardware documentation, and version control.

## Key Features
- Wireless remote control (Bluetooth / RF / Wi-Fi)
- DC motor control using motor driver module
- Modular embedded firmware architecture
- Battery-powered system with onboard regulation

## Technologies Used
- Microcontroller: ESP32 C3 SUPERMINI
- Motor Driver: TB6612FNG
- 360 Stepdown Buck Converter
- N20 Motors 12v 500rpm
- 11.1v LiPo Battery
- ipega PG9090 Wireless Controller
- Programming Language: C
- Version Control: Git & GitHub
- Documentation: Markdown, diagrams

## Components Breakdown
- ESP32 Microcontroller: Selected for its dual-core capability and integrated Bluetooth stack, allowing simultaneous communication and motor control.
- TB6612FNG Motor Driver: Chosen over the L298N for its higher efficiency (MOSFET-based) and smaller form factor, reducing heat and weight.
- N20 Motors (12V 500RPM): High-torque micro-geared motors that provide the necessary acceleration for tight track corners.
- 360 Buck Converter: An ultra-compact DC-DC step-down module used to efficiently regulate the 11.1V LiPo voltage down to 5V for logic components.
- Ipega PG9090: A low-latency wireless controller that provides precise analog input for the steering servo and throttle.

## Hardware Architecture
The hardware design centers on a Split-Rail Power Distribution strategy. To maximize the performance of the N20 motors, they are driven directly by the 11.1V battery potential via the TB6612FNG H-Bridge. Simultaneously, a 360 Buck Converter provides a stabilized 5V logic rail. This architecture prevents 'brownouts' (voltage drops) during high-current motor draws, ensuring the ESP32 and Steering Servo maintain consistent logic levels throughout the race.


## Software Architecture


## Wiring Diagram
The wiring diagram illustrates the physical interconnectivity of the vehicle’s electronic suite. Key design choices include the use of Common Grounding across all components to eliminate signal noise and the utilization of high-speed PWM-capable GPIOs on the ESP32. This map serves as the primary assembly guide, ensuring correct pin-mapping between the microcontroller logic and the high-power motor driver


## Project Documentation




