//
//
//  Team 6819 - Library methods which are shared between user control and autonomous modes.
//
//

//
//  We can fine tune the robot's responsiveness here
//
const int slowSpeed = 3;
const int superSlowSpeed = 6;
const int slowestSpeed = 10;

int joySlow = 5;				//Slow Driving Mode
int joySuperSlow = 6; 	//Super Slow Driving Mode

// Allow joystick interface
#include "joystickdriver.c"

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

//
//  Scales joysticks on Log scale for precise slow movement
//
const bool bLogarithmicScale = true;
const bool kMaximumPowerLevel = 100;  // Adjust to set max power level to be used.


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
	motor[ArmExtender] =  setPowRight;
	motor[ArmRaiser]  =  setPowLeft;
}

void ArmControl(int y1, int y2)
{
	int powLeft = -(scaleJoystick(y1));   // Left  hand joystick, y value.
	int powRight = (scaleJoystick(y2));   // Right hand joystick, y value.

	SetCrane(powLeft, powRight);
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

	SetMotors(powLeft, powRight);
}


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
