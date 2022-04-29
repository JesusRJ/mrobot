#ifndef Arms_h
#define Arms_h
#include <Servo.h>
#if ARDUINO > 22
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define SHOULDER_PIN 6
#define ELBOW_PIN 5
#define GRIPPER_PIN 9

class Arms
{
public:
    Arms();
    void config_servos();
    void moveShoulder(int);
    void moveElbow(int);
    void moveGripper(byte);

private:
    Servo _servoShoulder;
    Servo _servoElbow;
    Servo _servoGripper;
    void startPosition();
};

#endif
