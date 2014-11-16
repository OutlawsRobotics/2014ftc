#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Hubs,  S4, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          Sweeper,       tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorB,          BackDoor,      tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motorLeft,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorRight,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S4_C1_1,     ArmRaiser,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S4_C1_2,     ArmExtender,   tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S2_C1_1,    back_left,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    back_right,           tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    bucket,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 					User Control Mode A - from http://www.robotc.net/wiki/TETRIX_FTC_Templates
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
#include "lib/common6819.c"			// Team 6819 methods library.  Common between autonomous and user control mode.

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Support Methods - Lower level commands we'll use to command our robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{

  // Place code here to initialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

	// Play to indicate we are ready to go.
  Muppets();
     	// servoTarget[back_left] = min_servo;
   		// servoTarget[back_right] = min_servo;
  		eraseDisplay();
  		writeDebugStreamLine("left: %d right: %d",ServoValue[back_left],ServoValue[back_right]);
	return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Routine
//
// The following is the main code for the autonomous robot operation.
//
// At the end of the autonomous period, the FMS will autonmatically abort (stop) execution of the program
// and run the program defined as our User Control Script.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
  initializeRobot();

  waitForStart();

  	// User Control code goes here.

  	// Drive manually
  while( true ) {
		Tank(joystick.joy1_y1, joystick.joy1_y2);
    ArmControl(joystick.joy2_y1,joystick.joy2_y2);
    servoUp();
    servoDown();
 	  SetBucketUp();
 	  SetBucketDown();
		ControlSweeperForward();
		ControlSweeperBackward();
		ControlBackdoorUp();
		ControlBackdoorDown();

 	  }
	return;
}
