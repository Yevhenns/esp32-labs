#include <Arduino.h>
#include "motorHandler.h"

const int ch1 = 0;
const int ch2 = 1;
const int ch3 = 2;
const int ch4 = 3;

const int MIN_SPEED = 30;

void setRightMotor(int speed)
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

void setLeftMotor(int speed)
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