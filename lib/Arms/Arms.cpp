#include "Arms.h"
#include <Servo.h>
#if ARDUINO > 22
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

int startShoulder = 90;
int startElbow = 90;
int startGripper = 100;

int posShoulder = 90;
int posElbow = 90;
int posGripper = 0;

int lastShoulder = 90;
int lastElbow = 90;
int lastGripper = 90;

Arms::Arms() {}

void Arms::config_servos()
{
    _servoShoulder.attach(SHOULDER_PIN, 400, 2600);
    _servoElbow.attach(ELBOW_PIN, 400, 2600);
    _servoGripper.attach(GRIPPER_PIN, 400, 2600);
    startPosition();
}

void Arms::startPosition()
{
    int angleShoulder = _servoShoulder.read();
    int angleElbow = _servoElbow.read();
    int angleGripper = _servoGripper.read();

    posShoulder = angleShoulder;
    posElbow = angleElbow;
    posGripper = angleGripper;

    _servoShoulder.write(posShoulder);
    _servoElbow.write(posElbow);
    _servoGripper.write(posGripper);
}

void Arms::update(byte shoulder, byte elbow, byte gripper)
{
    int angleShoulder = SHOLDER_MIN;
    int angleElbow = ELBOW_MIN;

    // Move shoulder
    if (shoulder < 128)
    {
        angleShoulder = map(shoulder, 127, 0, 90, 180);
    }
    else if (shoulder > 128)
    {
        angleShoulder = map(shoulder, 129, 255, 0, 90);
    }
    moveShoulder(angleShoulder);

    // Move elbow
    if (elbow < 128)
        angleElbow = map(elbow, 127, 0, 0, 90);
    // else if (elbow > 128)
    //     angleElbow = map(elbow, 129, 255, 90, 0);
    else
        angleElbow = ELBOW_MIN;

    moveElbow(angleElbow);

    moveGripper(gripper);
}

void Arms::moveShoulder(byte pos)
{
    int p = constrain(pos, SHOLDER_MIN, SHOLDER_MAX);
    if (p != posShoulder)
    {
        posShoulder = p;
        _servoShoulder.write(posShoulder);
    }
}

void Arms::moveElbow(byte pos)
{
    int p = constrain(pos, ELBOW_MIN, ELBOW_MAX);
    if (p != posElbow)
    {
        posElbow = p;
        _servoElbow.write(posElbow);
    }
}

void Arms::moveGripper(byte pos)
{
    int p = constrain(pos, GRIPPER_MIN, GRIPPER_MAX);
    if (p != posGripper)
    {
        posGripper = p;
        _servoGripper.writeMicroseconds(posGripper);
    }
}