#include <Arduino.h>
#include <ESP32Servo.h>

Servo myServo;
int yellowLedPin = 25;
int greenLedPin = 12;
int servoPin = 26;
int buttonPin = 13;
int buzzerPin = 33;
int redLedPin = 15;
int buttonState = 0;
int ServState = 0;

void setup()
{
  myServo.attach(servoPin);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  myServo.write(90);
}

void beep(int freq, int duration)
{
  tone(buzzerPin, freq);
  delay(duration);
  noTone(buzzerPin);
}

void beepWarning()
{
  for (int i = 0; i < 5; i++)
  {
    beep(1500, 400);
    delay(100);
  }
}

void ledActions(int green, int red, int yellow)
{
  digitalWrite(greenLedPin, green);
  digitalWrite(redLedPin, red);
  digitalWrite(yellowLedPin, yellow);
}

void handHandler()
{
  if (ServState == 0)
  {
    myServo.write(115);
    ledActions(0, 0, 1);
    beep(1500, 300);
    beep(2000, 500);
    delay(500);
    ServState = 1;
  }
  else
  {
    myServo.write(85);
    ledActions(0, 1, 0);
    beepWarning();
    ServState = 0;
  }
  myServo.write(90);
}

void loop()
{
  ledActions(1, 0, 0);
  buttonState = digitalRead(buttonPin);
  if (buttonState == 0)
  {
    handHandler();
  }
}