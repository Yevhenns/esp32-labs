#include <Arduino.h>

const int in1 = 13;
const int in2 = 12;
const int in3 = 14;
const int in4 = 27;

const int LeftXPin = 26;
const int LeftYPin = 25;

const int pwmFreq = 1000;
const int pwmResolution = 8;

const int ch1 = 0;
const int ch2 = 1;
const int ch3 = 2;
const int ch4 = 3;

int centerX = 0;
int centerY = 0;

const int DEAD_ZONE = 200;
const int MIN_SPEED = 30;

int normalizeAxis(int value, int center)
{
  if (abs(value - center) < DEAD_ZONE)
  {
    return 0;
  }

  if (value < center)
  {
    return map(value, 0, center - DEAD_ZONE, -255, 0);
  }
  else
  {
    return map(value, center + DEAD_ZONE, 4095, 0, 255);
  }
}

void setLeftMotor(int speed)
{
  speed = constrain(speed, -255, 255);

  if (abs(speed) < MIN_SPEED)
    speed = 0;

  if (speed > 0)
  {
    ledcWrite(ch1, speed);
    ledcWrite(ch2, 0);
  }
  else if (speed < 0)
  {
    ledcWrite(ch1, 0);
    ledcWrite(ch2, -speed);
  }
  else
  {
    ledcWrite(ch1, 0);
    ledcWrite(ch2, 0);
  }
}

void setRightMotor(int speed)
{
  speed = constrain(speed, -255, 255);

  if (abs(speed) < MIN_SPEED)
    speed = 0;

  if (speed > 0)
  {
    ledcWrite(ch3, speed);
    ledcWrite(ch4, 0);
  }
  else if (speed < 0)
  {
    ledcWrite(ch3, 0);
    ledcWrite(ch4, -speed);
  }
  else
  {
    ledcWrite(ch3, 0);
    ledcWrite(ch4, 0);
  }
}

void setup()
{
  Serial.begin(115200);

  ledcSetup(ch1, pwmFreq, pwmResolution);
  ledcSetup(ch2, pwmFreq, pwmResolution);
  ledcSetup(ch3, pwmFreq, pwmResolution);
  ledcSetup(ch4, pwmFreq, pwmResolution);

  ledcAttachPin(in1, ch1);
  ledcAttachPin(in2, ch2);
  ledcAttachPin(in3, ch3);
  ledcAttachPin(in4, ch4);

  delay(1000);

  centerX = analogRead(LeftXPin);
  centerY = analogRead(LeftYPin);

  Serial.println("Center calibrated:");
  Serial.print("X: ");
  Serial.println(centerX);
  Serial.print("Y: ");
  Serial.println(centerY);

  setLeftMotor(0);
  setRightMotor(0);
}

void loop()
{
  int x = analogRead(LeftXPin);
  int y = analogRead(LeftYPin);

  int forward = normalizeAxis(y, centerY);
  int turn = -normalizeAxis(x, centerX);

  int leftSpeed = forward + turn;
  int rightSpeed = forward - turn;

  leftSpeed = constrain(leftSpeed, -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);

  setLeftMotor(leftSpeed);
  setRightMotor(rightSpeed);

  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.print(y);
  Serial.print(" L: ");
  Serial.print(leftSpeed);
  Serial.print(" R: ");
  Serial.println(rightSpeed);

  delay(20);
}