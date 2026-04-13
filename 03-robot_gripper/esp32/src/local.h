/*
  Minimal Esp8266 Websockets Client

  This sketch:
        1. Connects to a WiFi network
        2. Connects to a Websockets server
        3. Sends the websockets server a message ("Hello Server")
        4. Sends the websocket server a "ping"
        5. Prints all incoming messages while the connection is open

    NOTE:
    The sketch dosen't check or indicate about errors while connecting to
    WiFi or to the websockets server. For full example you might want
    to try the example named "Esp8266-Client".

  Hardware:
        For this sketch you only need an ESP8266 board.

  Created 15/02/2019
  By Gil Maimon
  https://github.com/gilmaimon/ArduinoWebsockets

*/

#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include "secrets.h"
#include <ESP32Servo.h>
#include <ArduinoJson.h>
Servo myServo;

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;
const char *websockets_server_host = WS_HOST;
const uint16_t websockets_server_port = WS_PORT;

using namespace websockets;

void onMessageCallback(WebsocketsMessage message)
{
    Serial.print("Got Message: ");
    Serial.println(message.data());

    StaticJsonDocument<100> doc;
    DeserializationError error = deserializeJson(doc, message.data());
    if (error)
    {
        Serial.println("JSON parsing failed");
        return;
    }

    const char *action = doc["action"];
    if (strcmp(action, "grab") == 0)
    {
        myServo.write(100);
        Serial.println("Servo grabbed!");
    }
    if (strcmp(action, "release") == 0)
    {
        myServo.write(80);
        Serial.println("Servo released!");
    }
    if (strcmp(action, "stop") == 0)
    {
        myServo.write(90);
        Serial.println("Servo stopped!");
    }
}

void onEventsCallback(WebsocketsEvent event, String data)
{
    if (event == WebsocketsEvent::ConnectionOpened)
    {
        Serial.println("Connnection Opened");
    }
    else if (event == WebsocketsEvent::ConnectionClosed)
    {
        Serial.println("Connnection Closed");
    }
    else if (event == WebsocketsEvent::GotPing)
    {
        Serial.println("Got a Ping!");
    }
    else if (event == WebsocketsEvent::GotPong)
    {
        Serial.println("Got a Pong!");
    }
}

WebsocketsClient client;
void setup()
{
    Serial.begin(115200);
    myServo.attach(33);
    delay(500);
    myServo.write(90);
    // Connect to wifi
    WiFi.begin(ssid, password);

    // Wait some time to connect to wifi
    for (int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++)
    {
        Serial.print(".");
        delay(1000);
    }

    // run callback when messages are received
    client.onMessage(onMessageCallback);

    // run callback when events are occuring
    client.onEvent(onEventsCallback);

    // Connect to server
    client.connect(websockets_server_host, websockets_server_port, "/");

    // Send a message
    // client.send("Hello Server");
    client.send("{\"action\":\"hello\"}");

    // Send a ping
    client.ping();
}

void loop()
{
    client.poll();
}