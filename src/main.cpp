#include <PS2X_lib.h>
#include <Motors.h>
#include <Arms.h>

// right now, the library does NOT support hot pluggable controllers, meaning
// you must always either restart your Arduino after you conect the controller,
// or call config_gamepad(pins) again after connecting the controller.
int error = 0;
byte type = 0;
byte vibrate = 0;

// Gamepad Pin definitions
#define GPCLK 13
#define GPCMD 11
#define GPATT 10
#define GPDAT 12

// Create PS2 Controller Class
PS2X ps2x;

// Create robo parts
Motors motors;
Arms arms;

// Gripper position
int gripperPos = GRIPPER_MIN;

void setup()
{
  Serial.begin(57600);
  gripperPos = GRIPPER_MIN;
  arms.config_servos();

  // setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(GPCLK, GPCMD, GPATT, GPDAT, true, true);

  if (error == 0)
  {
    Serial.println("Found Controller, configured successful");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Go to www.billporter.info for updates and to report bugs.");
  }

  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  type = ps2x.readType();
  switch (type)
  {
  case 0:
    Serial.println("Unknown Controller type");
    break;
  case 1:
    Serial.println("DualShock Controller Found");
    break;
  case 2:
    Serial.println("GuitarHero Controller Found");
    break;
  }
}

void moveByStick()
{
  byte plx = ps2x.Analog(PSS_LX);
  byte ply = ps2x.Analog(PSS_LY);

  Serial.print(plx);
  Serial.print(",");
  Serial.println(ply);

  if (
      (plx == 128 && ply == 128) ||
      ((plx > 120 && plx < 136) &&
       (ply > 120 && ply < 136)))
  {
    motors.stop();
    return;
  }

  if (ply < 128)
  {
    int speed = map(ply, 0, 128, 255, 0);
    motors.forward(speed);
  }
  else if (ply > 128)
  {
    int speed = map(ply, 128, 255, 0, 255);
    motors.backward(speed);
  }
  else if (plx < 128)
  {
    int speed = map(plx, 0, 128, 255, 0);
    motors.left(speed);
  }
  else if (plx > 128)
  {
    int speed = map(plx, 128, 255, 0, 255);
    motors.right(speed);
  }
  // else
  // {
  //   motors.stop();
  // }
}

void moveByButtons()
{
  if (ps2x.Button(PSB_PAD_UP))
  {
    // byte speed = ps2x.Analog(PSAB_PAD_UP);
    motors.forward(MAX_SPEED);
  }
  if (ps2x.Button(PSB_PAD_DOWN))
  {
    // byte speed = ps2x.Analog(PSAB_PAD_DOWN);
    motors.backward(MAX_SPEED);
  }
  if (ps2x.Button(PSB_PAD_RIGHT))
  {
    // byte speed = ps2x.Analog(PSAB_PAD_RIGHT);
    motors.right(MAX_SPEED);
  }
  if (ps2x.Button(PSB_PAD_LEFT))
  {
    // byte speed = ps2x.Analog(PSAB_PAD_LEFT);
    motors.left(MAX_SPEED);
  }

  if (ps2x.ButtonReleased(PSB_PAD_UP) || ps2x.ButtonReleased(PSB_PAD_DOWN) || ps2x.ButtonReleased(PSB_PAD_RIGHT) || ps2x.ButtonReleased(PSB_PAD_LEFT))
  {
    motors.stop();
  }
}

void loop()
{
  // skip loop if no controller found
  if (error == 1)
    return;

  // read controller and set large motor to spin at 'vibrate' speed
  ps2x.read_gamepad(false, vibrate);

  moveByButtons();
  // moveByStick();

  byte prx = ps2x.Analog(PSS_RX);
  byte pry = ps2x.Analog(PSS_RY);

  arms.update(pry, prx, gripperPos);

  delay(50);
}
