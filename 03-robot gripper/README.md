# ESP32 Robot Gripper

A small robotic arm with a gripper controlled via ESP32 and web interface

## Features:

- Real-time control via web buttons or keyboard (W/S)
- Backend built with Express.js and WebSockets
- Frontend built with React
- ESP32 handles Wi-Fi connection and communicates with the backend

## Subprojects / Documentation

- [Frontend README](./frontend/README.md) – web interface, controls, live angle display
- [Backend README](./backend/README.md) – Express.js server, WebSockets, angle updates
- [ESP32 README](./esp32/README.md) – firmware, Wi-Fi setup, Socket.IO communication
