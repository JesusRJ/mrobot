#include "Motors.h"
#include <L298N.h>

// Create Motor instances
L298N motorLeft(ENA, IN1, IN2);
L298N motorRight(ENB, IN3, IN4);

Motors::Motors()
{
}

void Motors::forward(unsigned short speed)
{
    motorLeft.setSpeed(speed);
    motorRight.setSpeed(speed);
    motorLeft.forward();
    motorRight.forward();
};

void Motors::backward(unsigned short speed)
{
    motorLeft.setSpeed(speed);
    motorRight.setSpeed(speed);
    motorLeft.backward();
    motorRight.backward();
};

void Motors::left(unsigned short speed)
{
    motorLeft.setSpeed(speed);
    motorRight.setSpeed(speed);
    motorLeft.backward();
    motorRight.forward();
};

void Motors::right(unsigned short speed)
{
    motorLeft.setSpeed(speed);
    motorRight.setSpeed(speed);
    motorLeft.forward();
    motorRight.backward();
};

void Motors::stop()
{
    motorLeft.stop();
    motorRight.stop();
};