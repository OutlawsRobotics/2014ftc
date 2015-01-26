//
// Team 6819 Autonomous Library. Code for fucntions for autonomous mode will go here.
//

#include "common6819.c"

void SetIR {
    if(HTIRS2readACDir === 5) {
        motor[motorRight] = 50;
        motor[motorLeft] = 50;
        wait10Msec(5);
        IRDump();
    } else if(HTIRS2readACDir < 5) {
        motor[motorRight] = 50;
        motor[motorLeft] = 0;
        wait10Msec(5);
        motor[motorLeft] = 50;
        motor[motorRight] = 0;
        wait10Msec(5);
        IRDump();
    } else if(HTIRS2readACDir > 5) {
        motor[motorLeft] = 50;
        motor[motorRight] = 0;
        wait10Msec(5);
        motor[motorRight] = 50;
        motor[motorLeft] = 0;
        wait10Msec(5);
        IRDump();
    }
}

void SetUS {
    if(USreadDist)
}