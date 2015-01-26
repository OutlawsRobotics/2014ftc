#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Hubs,  S4, HTMotor,  none,     none,     none)
#pragma config(Sensor, S3,     HTSMUX,         sensorI2CCustom)
#pragma config(Motor,  motorA,          Sweeper,       tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,          BackDoor,      tmotorNXT, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorLeft,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorRight,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S4_C1_1,     ArmRaiser,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S4_C1_2,     ArmExtender,   tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S2_C1_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_3,    bucket_servo,         tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    back_left,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_6,    back_right,           tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Autonomous Mode A
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
#include "lib/auto6819.c"  // Team methods common between AU and UC modes
#include "drivers/suite/drivers/hitechnic-sensormux.h"

// Assuming the Sensor MUX is connected to NXT sensor port 4 (S4)
// Assuming the following sensors are connected to the Sensor MUX ports:
// Port 1: IR
// Port 2: Sonar
// Port 3: Gyro
// Port 4: Not used
#include "drivers/suite/drivers/hitechnic-gyro.h"    //for gyro sensor
#include "drivers/suite/drivers/lego-ultrasound.h"    //for sonar sensor
#include "drivers/suite/drivers/hitechnic-irseeker-v2.h"    //for IR seeker sensor

#define IRSensor                msensor_S3_2
#define sonarSensor             msensor_S3_1
#define gyroSensor              msensor_S3_3


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

	// Play to indicate we are ready to go.
  Muppets();
  clearDebugStream();
  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Main Autonomous Routine
//
//  The following is the main code for the autonomous robot operation.
//
//  When AU mode is done, the system will run the paired UC script.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
  initializeRobot();

  waitForStart(); // Wait for the beginning of autonomous phase.

    int seconds = 0;
		/* Arm45();
    Tank( 100, 100);
		wait10Msec(400);
		Tank ( 0, 0); */


		int Sonar1value = USreadDist(sonarSensor);

    writeDebugStreamLine("Sonar Value: %d", Sonar1value);

    int IR1value = HTIRS2readACDir(IRSensor);

    writeDebugStreamLine("IR Value: %d", IR1value);

    int Gyro1value = HTGYROreadRot(gyroSensor);

    writeDebugStreamLine("Gyro Value: %d", Gyro1value);

    HTGYROstartCal(gyroSensor);
// int gyroRotation = HTGYROreadRot(gyroSensor);
// int distanceInCM = USreadDist(sonarSensor);
// int irACDirection = HTIRS2readACDir(IRSensor);


}
