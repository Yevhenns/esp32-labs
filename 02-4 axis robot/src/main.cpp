#include <Arduino.h>
#include <ESP32Servo.h>

Servo myServo1;
Servo myServo2;
Servo myServo3;
Servo myServo4;

int firstServoPin = 4;
int secondServoPin = 5;
int thirdServoPin = 6;
int fourthServoPin = 7;

int LeftXPin = 32;
int LeftYPin = 33;
int RightXPin = 34;
int RightYPin = 35;

void setup()
{
  myServo1.attach(firstServoPin);
  myServo2.attach(secondServoPin);
  myServo3.attach(thirdServoPin);
  myServo4.attach(fourthServoPin);

  myServo1.write(90);
  myServo2.write(90);
  myServo3.write(90);
  myServo4.write(90);
}

void moveHandler(int value, Servo &servo)
{
  if (value >= 500 && value <= 550)
  {
    servo.write(90);
  }
  if (value < 400)
  {
    servo.write(85);
  }
  if (value > 800)
  {
    servo.write(95);
  }
}

void handleAxis(int pin, Servo &servo)
{
  int value = analogRead(pin);
  moveHandler(value, servo);
}

void loop()
{
  handleAxis(LeftXPin, myServo1);
  handleAxis(LeftYPin, myServo2);
  handleAxis(RightXPin, myServo3);
  handleAxis(RightYPin, myServo4);
}