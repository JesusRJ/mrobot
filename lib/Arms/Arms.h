#ifndef Arms_h
#define Arms_h
#include <Servo.h>
#if ARDUINO > 22
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define SHOULDER_PIN 5
#define GRIPPER_PIN 6
#define ELBOW_PIN 7
#define SERVO_DELAY 50

#define SHOLDER_MIN 100
#define SHOLDER_MAX 170
#define ELBOW_MIN 40
#define ELBOW_MAX 100
#define GRIPPER_MIN 110
#define GRIPPER_MAX 137

class Arms
{
public:
    Arms();
    void config_servos();
    void update(byte shoulder, byte elbow, byte gripper);

private:
    Servo _servoShoulder;
    Servo _servoElbow;
    Servo _servoGripper;
    void startPosition();
    void moveShoulder(byte);
    void moveElbow(byte);
    void moveGripper(byte);
};

#endif
