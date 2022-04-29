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

int minShoulder = 0;
int maxShoulder = 150;
int minElbow = 0;
int maxElbow = 150;
int minGripper = 0;
int maxGripper = 150;

Arms::Arms() {}

void Arms::config_servos()
{
    _servoShoulder.attach(SHOULDER_PIN);
    _servoElbow.attach(ELBOW_PIN);
    _servoGripper.attach(GRIPPER_PIN);
    startPosition();
}

void Arms::startPosition()
{
    // int angleShoulder = _servoShoulder.read();
    // int angleElbow = _servoElbow.read();
    // int angleGripper = _servoGripper.read();

    posShoulder = startShoulder;
    posElbow = startElbow;
    posGripper = startGripper;

    _servoShoulder.write(posShoulder);
    _servoElbow.write(posElbow);
    _servoGripper.write(posGripper);
}

void Arms::moveShoulder(int pos)
{
    posShoulder = pos;
    _servoShoulder.write(posShoulder);
}

void Arms::moveElbow(int pos)
{
    posElbow = pos;
    _servoElbow.write(posElbow);
}

void Arms::moveGripper(byte pos)
{
    posGripper = pos;
    Serial.print("  > posGripper: ");
    Serial.print(posGripper);
    _servoGripper.write(posGripper);
}