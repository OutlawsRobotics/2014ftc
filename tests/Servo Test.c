#pragma config(Hubs,  S3, HTServo,  none,     none,     none)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"/



task main()
{
 servo[servo1] = 100;
 servo[servo2] = 155;

 wait1Msec(5000);

 while(true)

 getJoystickSettings (joystick);

 servo[servo1] = joystick.joy1_y1 + 127;
 servo[servo2] =  (255  (joystick.joy1_y1 + 127));


}
