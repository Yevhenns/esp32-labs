const express = require('express');
const http = require('http');
const { WebSocketServer, WebSocket } = require('ws');

const app = express();

app.get('/', (req, res) => {
  res.send('OK');
});

const server = http.createServer(app);
const wss = new WebSocketServer({ noServer: true });

wss.on('connection', (ws) => {
  console.log('Client connected');

  ws.on('message', (message) => {
    try {
      let text = '';

      if (typeof message === 'string') {
        text = message;
      } else if (Buffer.isBuffer(message)) {
        text = message.toString();
      }

      const data = JSON.parse(text);

      if (data?.action) {
        console.log('Action:', data);

        const messageToSend = JSON.stringify({ action: data.action });

        wss.clients.forEach((client) => {
          if (client.readyState === WebSocket.OPEN) {
            client.send(messageToSend);
          }
        });
      }
    } catch (e) {
      console.log('Invalid message');
    }
  });

  ws.on('close', () => {
    console.log('Client disconnected');
  });
});

server.on('upgrade', (req, socket, head) => {
  if (req.url === '/ws') {
    wss.handleUpgrade(req, socket, head, (ws) => {
      wss.emit('connection', ws, req);
    });
  } else {
    socket.destroy();
  }
});

const PORT = process.env.PORT || 10000;
server.listen(PORT, () => {
  console.log('Server running on port', PORT);
});
