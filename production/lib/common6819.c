//
//
//  Team 6819 - Library methods which are shared between user control and autonomous modes.
//
//

// Note: Check out http://botbench.com/blog/robotc-driver-suite/

//
//  We can fine tune the robot's responsiveness here
//

const int slowSpeed = 3;
const int superSlowSpeed = 6;
const int slowestSpeed = 10;

int joySlow = 5;				//Slow Driving Mode
int joySuperSlow = 6; 	//Super Slow Driving Mode

// bool drivingOn = true;

int defaultMovementSpeed = 50;
int turnSpeed = 30;

// float rotSpeed = 0;
float heading = 0;

bool tankSpeed = true;
bool armSpeed = true;

// Allow joystick interface
#include "joystickdriver.c"
// #include "hitechnic-gyro.h"

// Define Button hexcodes
#define button1   0x01
#define button2   0x02
#define button3   0x04
#define button4   0x08
#define button5   0x10
#define button6   0x20
#define button7   0x40
#define button8   0x80
#define button9  0x100
#define button10 0x200


// Play init tune
void Muppets()
{
  //        250 = Tempo
  //          5 = Default octave
  //    Quarter = Default note length
  //        10% = Break between notes
  //

  PlayTone(  523,   11); wait1Msec( 120);  // Note(C, Duration(Eighth))
  PlayTone(  587,   11); wait1Msec( 120);  // Note(D, Duration(Eighth))
  PlayTone(  659,   22); wait1Msec( 240);  // Note(E)
  PlayTone(  659,   11); wait1Msec( 120);  // Note(E, Duration(Eighth))
  PlayTone(  587,   22); wait1Msec( 240);  // Note(D)
  PlayTone(  587,   11); wait1Msec( 120);  // Note(D, Duration(Eighth))
  PlayTone(  523,   22); wait1Msec( 240);  // Note(C)
  return;

}


// All done tones.
void Cocacola()
{
  //        125 = Tempo
  //          5 = Default octave
  //    Quarter = Default note length
  //        10% = Break between notes
  //

  PlayTone(  988,   22); wait1Msec( 240);  // Note(E6, Duration(Eighth))
  PlayTone( 1320,   22); wait1Msec( 240);  // Note(A6, Duration(Eighth))
  PlayTone( 1109,   43); wait1Msec( 480);  // Note(F#6)
  PlayTone(  880,   43); wait1Msec( 480);  // Note(D6)
  PlayTone(    0,   86); wait1Msec( 960);  // Note(Rest, Duration(Half))
  return;
}

//
//  Scales joysticks on Log scale for precise slow movement
//

const bool bLogarithmicScale = true;
const bool kMaximumPowerLevel = 100;  // Adjust to set max power level to be used.

void resetHeading(){
	heading = 0;
}

//  Read about encoders here.
//  http://www.education.rec.ri.cmu.edu/previews/robot_c_products/teaching_rc_tetrix_preview/sensing/forwardfordistance/documents/encoders_helper.pdf

// Encoder reset

void resetEncoders()
{
	nMotorEncoder[motorRight] = 0;
	nMotorEncoder[motorLeft] = 0;
}

int inchesToEncoder(int inches)
{
	// Returns encoder value from inches
	// Encoder Rotation 1024, wheel circumference = 14.92256, encoders/inch = 86.9198195873

	return inches * 107.75;
}

// Motors may not encode at the same rate.  Average.

int averageEncoders()
{
	return ((nMotorEncoder[motorRight] + nMotorEncoder[motorLeft])/2);
}

int turningEncoders(int dir)
{
	return (dir*(nMotorEncoder[motorRight]*-1 + nMotorEncoder[motorLeft])/2);
}


// Set motor speed

void SetMotors(int setPowLeft, int setPowRight)
{
	//if (setPowLeft > motor[motorLeft]){
	//	motor[motorLeft]=motor[motorLeft]+1;
	//}
	//else if (setPowLeft < motor[motorLeft]){
	//	motor[motorLeft]=motor[motorLeft]-1;
	//}

	//if (setPowRight > motor[motorRight]){
	//	motor[motorRight]=motor[motorRight]+1;
	//}
	//else if (setPowRight < motor[motorRight]){
	//	motor[motorRight]=motor[motorRight]-1;
	//}

	motor[motorRight] =  setPowRight;
	motor[motorLeft]  =  setPowLeft;
}


int moveStraight(int distance, int inchesOrEncoders = true, int speed = defaultMovementSpeed)
{
	resetEncoders();

	int encoderDistance = 0;

	if(inchesOrEncoders){
		encoderDistance = inchesToEncoder(distance);
	}
	else {
		encoderDistance = distance;
	}

	if (distance > 0){
		SetMotors(speed,speed);
		while (averageEncoders() < encoderDistance){
			wait1Msec(3);
		}
	}

	else{
		SetMotors(-speed,-speed);
		while (averageEncoders() > encoderDistance){
			wait1Msec(3);
		}
	}

	SetMotors(0,0);

	return averageEncoders();
}

int sign(int num)

{
	if (num<0){ return -1;}
	else { return 1;}
}

void turnDegrees(int deg)

{
	resetHeading();

	SetMotors(turnSpeed*sign(deg),turnSpeed*sign(deg)*-1);

	if (deg > 0){
		while (heading < deg){
			wait1Msec(3);
		}
	}
	else{
		while (heading > deg){
			wait1Msec(3);
		}
	}

	SetMotors(0,0);
}

/*
task updateGyro(){
	time1[T1] = 0;

	while (true)
	{
		// Wait until 20ms has passed
		while (time1[T1] < 20){
			wait1Msec(1);
		}

		// Reset the timer
		time1[T1]=0;

		// Read the current rotation speed
		rotSpeed = HTGYROreadRot(Gyro);

		// Calculate the new heading by adding the amount of degrees
		// we've turned in the last 20ms
		// If our current rate of rotation is 100 degrees/second,
		// then we will have turned 100 * (20/1000) = 2 degrees since
		// the last time we measured.
		heading += rotSpeed * 0.02;
	}

}
*/


// How fast are we trying to go?
int scaleJoystick(int &nJoy1, int nMaxValue = kMaximumPowerLevel)
{
	//
	// This function scales the joystick settings to the appropriate range for
	// controlling a NXT motor.
	//
	// Joystick values range from -128 to +127.
	// Speed/power settings for NXT motors range from -100 to +100
	//
	// The physical range of motion of a joystick is quite small and it is sometimes
	// hard to control slow speeds. So another capability of this program to apply
	// a "logarithmic" scale to the joystick settings.
	//
	static const int nLogScale[17] =
	{
		0,   5,   9,   10,
		12,  15,  18,  24,
		30,  36,  43,  50,
		60,  72,  85, 100,
		100
	};
	int nScaled;

	nScaled = nJoy1;
	if (bLogarithmicScale)
	{
		nScaled /= 8;
		if (nScaled >= 0)
			nScaled = nLogScale[nScaled];
		else
			nScaled = - nLogScale[ - nScaled];
	}
	nScaled *= nMaxValue;
	nScaled /= 100;
	return nScaled;
}


void SetCrane(int setPowLeft, int setPowRight)
{
	int powLeft  = scaleJoystick(setPowLeft);   // Left  hand joystick, y value.
	int powRight = scaleJoystick(setPowRight);   // Right hand joystick, y value.
	motor[ArmExtender] =  -powRight;
	motor[ArmRaiser]  =  -powLeft;
//	writeDebugStreamLine("ArmRaiser: %d", powLeft);
}

void servoDown(){
	getJoystickSettings(joystick);
		if (joy1Btn(1)){
		servoChangeRate[back_left]=2;
		servoChangeRate[back_right]=2;
		servo[back_right]=160;
		servo[back_left]=45;

  }
}
void servoUp(){
	getJoystickSettings(joystick);
		if (joy1Btn(2)){
			servoChangeRate[back_left]=2;
			servoChangeRate[back_right]=2;
			servo[back_right]=220;
			servo[back_left]=0;
			// writeDebugStreamLine("back_left: %d", joystick.joy1_Buttons);

  }
}

void ArmInit(){
	//ArmInit must go to 0.
	motor[ArmExtender]=100;
	motor[ArmRaiser]=-100;
	wait10Msec(55);
	motor[ArmRaiser]=0;
	wait10Msec(10);
	motor[ArmExtender]=0;

}

void Arm45(){
	//Arm45 takes us from 0 to 45.
		motor[ArmRaiser]=100;
		wait10Msec(75);
		motor[ArmRaiser]=0;
}

void Arm85(){
	//Arm85 takes us from 45 to 85 and extends arm from 0 to 100.
		motor[ArmRaiser]=100;
		wait10Msec(55);
		motor[ArmRaiser]=0;
		motor[ArmExtender]=-100;
		wait10Msec(5.5*100);
		motor[ArmExtender]=0;
		motor[ArmRaiser]=0;
		armSpeed = false;
}

void ArmReset(){
	//Resets arm to 45 from 85.
		armSpeed = true;
		motor[ArmExtender]=100;
		wait10Msec(7*100);
		motor[ArmExtender]=0;
		motor[ArmRaiser]=-100;
		wait10Msec(65);
		motor[ArmRaiser]=0;
	}
void Dump(){
	motor[ArmRaiser]=25;
	wait10Msec(10);
	motor[ArmRaiser]=0;
}

void setControlSpeed(){
	getJoystickSettings(joystick);
		if (joy1Btn(8)){
			tankSpeed = !tankSpeed;
			writeDebugStreamLine("TankSpeed %d", tankSpeed);
			wait10Msec(25);
	}
			if (joy2Btn(8)){
			armSpeed = !armSpeed;
			writeDebugStreamLine("armSpeed %d", armSpeed);
			wait10Msec(25);
	}
}

// This is our pouncer. This helps us collect balls.

void pouncer(){
	// Forward
	if(joy2Btn(4)){
		SetMotors(50, 50);
		wait10Msec(.25*100);
		SetMotors(0, 0);
		SetCrane(-100, 0);
		wait10Msec(.35*100);
		SetCrane(0, 0);
		SetCrane(100, 0);
		wait10Msec(.65*100);
		SetCrane(0, 0);

	}
	// Left
		if(joy2Btn(1)){
		SetMotors(25, 75);
		wait10Msec(.25*100);
		SetMotors(0, 0);
		SetCrane(-100, 0);
		wait10Msec(.35*100);
		SetCrane(0, 0);
		SetCrane(100, 0);
		wait10Msec(.65*100);
		SetCrane(0, 0);

	}
	// Right
		if(joy2Btn(3)){
		SetMotors(75, 25);
		wait10Msec(.25*100);
		SetMotors(0, 0);
		SetCrane(-100, 0);
		wait10Msec(.35*100);
		SetCrane(0, 0);
		SetCrane(100, 0);
		wait10Msec(.65*100);
		SetCrane(0, 0);
}
	// No move
		if(joy2Btn(2)){
    SetCrane(-100, 0);
    wait10Msec(.35*100);
  	SetCrane(0, 0);
  	SetCrane(100, 0);
  	wait10Msec(.65*100);
	}
}

  void IRDump() {
  	motor[ArmRaiser] = 100;
    wait10Msec(5);
    motor[ArmExtender] = 100;
    wait10Msec(5);
    Dump();
  }

void ArmControl(int y1, int y2)
{
	int powLeft = -(scaleJoystick(y1));   // Left  hand joystick, y value.
	int powRight = (scaleJoystick(y2));   // Right hand joystick, y value.
	if (!armSpeed){
	// This defines our speed.
	powLeft = powLeft/1.25;
	powRight = powRight/1.25;
	}

	SetCrane(powLeft, powRight);
	getJoystickSettings(joystick);
		if (joy2Btn(9)){
			ArmInit();
		}
		if (joy2Btn(10)){
			Arm45();
		}
		if (joy2Btn(5)){
			Arm85();
		}
		if (joy2Btn(7)){
			ArmReset();
		}
		if (joy2Btn(6)){
			Dump();
		}
}


int slowMode(int slow, int superSlow)
{
	if (slow == 1){
		if (superSlow == 1){
			return slowestSpeed;
		}
		else {
			return slowSpeed;
		}
	}

	if (superSlow == 1){
		return superSlowSpeed;
	}

	return 1;
}


//The Drive
void Tank(int y1, int y2)
{
	int powLeft  = scaleJoystick(y1)/slowMode(joy1Btn(joySlow),joy1Btn(joySuperSlow))*1.0;   // Left  hand joystick, y value.
	int powRight = scaleJoystick(y2)/slowMode(joy1Btn(joySlow),joy1Btn(joySuperSlow))*1.0;   // Right hand joystick, y value.
	if (!tankSpeed){
	// This defines our speed.
	powLeft = powLeft/6;
	powRight = powRight/6;
	}
	SetMotors(powLeft, powRight);

//	writeDebugStreamLine("scaleJoystick %d %d", y1, y2);

}
