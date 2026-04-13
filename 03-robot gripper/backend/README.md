## Description

Backend (Express.js)

Handles real-time communication between the frontend and the ESP32 using WebSocket (ws).

## Features

- Receives grab / release / stop commands from the frontend
- Broadcasts commands to all connected clients (including ESP32) via WebSocket
- Acts as a simple relay between frontend and hardware
- Built with Express.js and the ws library (no Socket.IO)

## Installation

```bash
$ npm install
```

```bash
$ npm run start
```
