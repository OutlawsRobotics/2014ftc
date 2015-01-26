#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Hubs,  S4, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
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
#include "lib/common6819.c"  // Team methods common between AU and UC modes

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
  ArmInit();

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
  	Arm45(); // Set the Arm from 0 to 45.
    // Drive manually
		Tank( -100, -100);
		wait10Msec(3*100); //This will add up to 5 seconds.
		Tank ( 0, 0);
		Muppets();
		int counter = 0;
		while(true){
		counter = counter+1;
		Tank( 100, 100);
		wait10Msec(.55*100); //This will add up to a 4th of a second.
		Tank ( 100, 0);
		wait10Msec(.1*100); //This will add up to a 10th of a second.
		Tank ( -100, -100);
		wait10Msec(.95*100);
		if (counter == 6) {
		break;
		}
}

  // Do our autonomous mode work here... some example code...

  // When done, robot will play endtone and wait for end of autonomous mode, then run user control script.
	Cocacola();

	return;
}
