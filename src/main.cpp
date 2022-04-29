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

void setup()
{
  Serial.begin(57600);

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

  // Serial.print(ps2x.Analog(1), HEX);

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

  // Set motors initial speed
  // motorLeft.setSpeed(255);
  // motorRight.setSpeed(255);
}
int pos = 100;
void loop()
{
  /* You must Read Gamepad to get new values
  Read GamePad and set vibration values
  ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
  if you don't enable the rumble, use ps2x.read_gamepad(); with no values

  you should call this at least once a second
  */

  if (error == 1) // skip loop if no controller found
    return;

  ps2x.read_gamepad(false, vibrate); // read controller and set large motor to spin at 'vibrate' speed

  // if (ps2x.Button(PSB_START)) // will be TRUE as long as button is pressed
  //   Serial.println("Start is being held");
  // if (ps2x.Button(PSB_SELECT))
  //   Serial.println("Select is being held");

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

  // Arms
  if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1))
  {
    // Serial.print("Stick Values: Left[");
    // Serial.print(ps2x.Analog(PSS_LX), DEC); // Left stick, Y axis. Other options: LX, RY, RX
    // Serial.print(",");
    // Serial.print(ps2x.Analog(PSS_LY), DEC);
    // Serial.print("] Rigth[");
    // Serial.print(ps2x.Analog(PSS_RX), DEC);
    // Serial.print(",");
    // Serial.print(ps2x.Analog(PSS_RY), DEC);
    // Serial.println("]");

    // arms.moveGripper(ps2x.Analog(PSS_RY));
    // arms.moveElbow(ps2x.Analog(PSS_RX));
  }

  if (ps2x.Button(PSB_L1))
  {
    if (pos > 100)
    {
      pos--;
      arms.moveGripper(pos);
    }
  }
  if (ps2x.Button(PSB_R1))
  {
    if (pos < 137)
    {
      pos++;
      arms.moveGripper(pos);
    }
  }

  // if (ps2x.ButtonReleased(PSB_PAD_DOWN))
  // {
  //   motors.stop();
  // }

  // vibrate = ps2x.Analog(PSAB_BLUE); // this will set the large motor vibrate speed based on
  //                                   // how hard you press the blue (X) button

  // if (ps2x.NewButtonState()) // will be TRUE if any button changes state (on to off, or off to on)
  // {

  //   if (ps2x.Button(PSB_L3))
  //     Serial.println("L3 pressed");
  //   if (ps2x.Button(PSB_R3))
  //     Serial.println("R3 pressed");
  //   if (ps2x.Button(PSB_L2))
  //     Serial.println("L2 pressed");
  //   if (ps2x.Button(PSB_R2))
  //     Serial.println("R2 pressed");
  //   if (ps2x.Button(PSB_GREEN))
  //     Serial.println("Triangle pressed");
  // }

  // if (ps2x.ButtonPressed(PSB_RED)) // will be TRUE if button was JUST pressed
  //   Serial.println("Circle just pressed");

  // if (ps2x.ButtonReleased(PSB_PINK)) // will be TRUE if button was JUST released
  //   Serial.println("Square just released");

  // if (ps2x.NewButtonState(PSB_BLUE)) // will be TRUE if button was JUST pressed OR released
  //   Serial.println("X just changed");

  // if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
  // {
  //   Serial.print("Stick Values: Left[");
  //   Serial.print(ps2x.Analog(PSS_LX), DEC); // Left stick, Y axis. Other options: LX, RY, RX
  //   Serial.print(",");
  //   Serial.print(ps2x.Analog(PSS_LY), DEC);
  //   Serial.print("] Rigth[");
  //   Serial.print(ps2x.Analog(PSS_RX), DEC);
  //   Serial.print(",");
  //   Serial.print(ps2x.Analog(PSS_RY), DEC);
  //   Serial.println("]");
  // }

  byte px = ps2x.Analog(PSS_LX);
  byte py = ps2x.Analog(PSS_LY);

  if (py < 128)
  {
    int speed = map(py, 0, 128, 255, 0);
    motors.forward(speed);
  }
  else if (py > 128)
  {
    int speed = map(py, 128, 255, 0, 255);
    motors.backward(speed);
  }
  else if (px < 128)
  {
    int speed = map(px, 0, 128, 255, 0);
    motors.left(speed);
  }
  else if (px > 128)
  {
    int speed = map(px, 128, 255, 0, 255);
    motors.right(speed);
  }
  else
  {
    motors.stop();
  }

  delay(50);
}