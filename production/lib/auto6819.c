//
// Team 6819 Autonomous Library. Code for fucntions for autonomous mode will go here.
//

void SetIR(){
	int IRVal = HTIRS2readACDir(IRSensor);
    if(IRVal == 5) {
        motor[motorRight] = 50;
        motor[motorLeft] = 50;
        wait10Msec(5);
        IRDump();
    } else if(IRVal < 5) {
        motor[motorRight] = 50;
        motor[motorLeft] = 0;
        wait10Msec(5);
        motor[motorLeft] = 50;
        motor[motorRight] = 0;
        wait10Msec(5);
        IRDump();
    } else if(IRVal > 5) {
        motor[motorLeft] = 50;
        motor[motorRight] = 0;
        wait10Msec(5);
        motor[motorRight] = 50;
        motor[motorLeft] = 0;
        wait10Msec(5);
        IRDump();
    }
}
