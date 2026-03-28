# ESP32 Simple Robotic Hand

Firmware for controlling a small robotic hand with an ESP32, a servo, LEDs, a buzzer, and a button.

## Features

- Control a servo motor (gripper) with a push button
- Three LEDs indicate the current state (green, red, yellow)
- Buzzer signals opening/closing actions with different tones
- Servo returns to neutral position after each action

## Hardware Setup

ESP32 pins:

- Servo → GPIO 26
- Button → GPIO 13 (INPUT_PULLUP)
- Buzzer → GPIO 33
- Red LED → GPIO 15
- Yellow LED → GPIO 25
- Green LED → GPIO 12
- Power: ESP32 3.3V/5V (check servo requirements)

## How It Works

1. Initial state: Servo at 90°, green LED ON
2. Button pressed:

- If hand is closed → opens hand, yellow LED ON, buzzer beeps
- If hand is open → closes hand, red LED ON, warning buzzer pattern

3. After each action, servo returns to neutral (90°)

## Usage

- Connect hardware as above
- Upload code to ESP32
- Press the button to toggle hand open/close
