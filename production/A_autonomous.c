#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Hubs,  S4, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     MyFriendlyIR,   sensorHiTechnicIRSeeker600)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorRight,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorLeft,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S4_C1_1,     ArmExtender,   tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S4_C1_2,     ArmRaiser,     tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
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

  // Do our autonomous mode work here... some example code...

/*  //int IR1value = SensorValue(MyFriendlyIR);
	  //nxtDisplayCenteredBigTextLine( 5, "%d", IR1value );






			//Anthing below the IR data is irrelevant





			if(joystick1.joy1_y1(1) == 128)
	  	{
	  	nxtDisplayCenteredBigTextLine( 5, "joystick1Btn1", 1 );

	  	motor[driveRight]= 25;
		  }
		else
			{
			motor[driveRight]= 0;
		  }
		  */



  // Move forward
 	//motor(motorL) = 50;
 	//motor(motorR) = 50;

  // Turn right
 	//motor(motorL) = 0;
  //motor(motorR) = 50;
  //motor(motorR) = 0;

  // When done, robot will play endtone and wait for end of autonomous mode, then run user control script.
	Cocacola();

	return;
}
