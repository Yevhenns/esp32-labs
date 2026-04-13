## Description

ESP32 Firmware

Handles the robotic gripper hardware and communicates with the backend via WebSocket.

## Features

- Connects to Wi-Fi using credentials from secrets.h
- Establishes a WebSocket (ws) connection to the backend
- Receives gripper control commands
- Controls a servo motor based on incoming actions
- Designed for real-time control of the robotic gripper

## Installation / Flashing

- Open the project in Arduino IDE or PlatformIO
- Copy secrets.example.h to secrets.h and fill in your Wi-Fi credentials.
- Upload the firmware to the ESP32
