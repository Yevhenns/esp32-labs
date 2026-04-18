#include <Arduino.h>
#include <WebSocketsClient.h>
#include <WiFiMulti.h>
#include <ArduinoJson.h>
#include "secrets.h"
#include "motorHandler.h"

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;
const char *websockets_server_host = WS_HOST;
const uint16_t websockets_server_port = WS_PORT;
const char *websockets_server_url = WS_URL;

const int in1 = 13;
const int in2 = 12;
const int in3 = 14;
const int in4 = 27;

const int ch1 = 0;
const int ch2 = 1;
const int ch3 = 2;
const int ch4 = 3;

#define MSG_SIZE 256

WiFiMulti wifiMulti;
WebSocketsClient wsClient;

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

  if (strcmp(action, "forward") == 0)
  {
    setLeftMotor(150);
    setRightMotor(150);
  }
  else if (strcmp(action, "backward") == 0)
  {
    setLeftMotor(-150);
    setRightMotor(-150);
  }
  else if (strcmp(action, "left") == 0)
  {
    setLeftMotor(-150);
    setRightMotor(150);
  }
  else if (strcmp(action, "right") == 0)
  {
    setLeftMotor(150);
    setRightMotor(-150);
  }
  else if (strcmp(action, "stop") == 0)
  {
    setLeftMotor(0);
    setRightMotor(0);
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

  ledcAttachPin(in1, ch1);
  ledcAttachPin(in2, ch2);
  ledcAttachPin(in3, ch3);
  ledcAttachPin(in4, ch4);

  delay(1000);

  setLeftMotor(0);
  setRightMotor(0);

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