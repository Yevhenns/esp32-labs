#include <Arduino.h>
#include <WebSocketsClient.h>
#include <WiFiMulti.h>
#include <ESP32Servo.h>
#include <ArduinoJson.h>
#include "secrets.h"

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;
const char *websockets_server_host = WS_HOST;
const uint16_t websockets_server_port = WS_PORT;
const char *websockets_server_url = WS_URL;

#define MSG_SIZE 256

WiFiMulti wifiMulti;
WebSocketsClient wsClient;
Servo myServo;

void handleMessage(uint8_t *payload)
{
  StaticJsonDocument<100> doc;
  DeserializationError error = deserializeJson(doc, payload);
  if (error)
  {
    Serial.println("JSON parsing failed");
    return;
  }

  const char *action = doc["action"];
  if (!action)
    return;

  if (strcmp(action, "grab") == 0)
  {
    myServo.write(100);
    Serial.println("Servo grabbed!");
  }
  else if (strcmp(action, "release") == 0)
  {
    myServo.write(80);
    Serial.println("Servo released!");
  }
  else if (strcmp(action, "stop") == 0)
  {
    myServo.write(90);
    Serial.println("Servo stopped!");
  }
}

void onWSEvent(WStype_t type, uint8_t *payload, size_t length)
{
  switch (type)
  {
  case WStype_CONNECTED:
    Serial.println("WS Connected");
    wsClient.sendTXT("{\"action\":\"hello\"}");
    break;
  case WStype_DISCONNECTED:
    Serial.println("WS Disconnected");
    break;
  case WStype_TEXT:
    Serial.printf("WS Message: %s\n", payload);
    handleMessage(payload);
    break;
  default:
    break;
  }
}

void setup()
{
  Serial.begin(115200);
  myServo.attach(33);
  myServo.write(90);

  pinMode(LED_BUILTIN, OUTPUT);

  wifiMulti.addAP(ssid, password);
  Serial.print("Connecting to WiFi");
  while (wifiMulti.run() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi connected");

  wsClient.beginSSL(websockets_server_host, websockets_server_port, websockets_server_url, "", "wss");
  wsClient.onEvent(onWSEvent);
}

void loop()
{
  digitalWrite(LED_BUILTIN, WiFi.status() == WL_CONNECTED);
  wsClient.loop();
}