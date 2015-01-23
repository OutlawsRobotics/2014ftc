#pragma config(Sensor, S1,     HTSMUX,              sensorI2CCustom)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: hitechnic-force-SMUX-test1.c 133 2013-03-10 15:15:38Z xander $
 */

/**
 * HTCS-driver.h provides an API for the HiTechnic Force Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.59 AND HIGHER. 

 * Xander Soldaat (xander_at_botbench.com)
 * 30 September 2012
 * version 0.1
 */

#include "drivers/hitechnic-sensormux.h"
#include "drivers/hitechnic-force.h"

// The sensor is connected to the first port
// of the SMUX which is connected to the NXT port S1.
// To access that sensor, we must use msensor_S1_1.  If the sensor
// were connected to 3rd port of the SMUX connected to the NXT port S4,
// we would use msensor_S4_3

// Give the sensor a nice easy to use name
const tMUXSensor HTFORCE = msensor_S1_1;

task main() {
  int _force = 0;

  nNxtButtonTask  = -2;

  eraseDisplay();
  nxtDisplayCenteredTextLine(0, "HiTechnic");
  nxtDisplayCenteredBigTextLine(1, "Force");
  nxtDisplayCenteredTextLine(3, "SMUX Test");
  nxtDisplayCenteredTextLine(5, "Connect SMUX to");
  nxtDisplayCenteredTextLine(6, "S1 and sensor to");
  nxtDisplayCenteredTextLine(7, "SMUX Port 1");
  wait1Msec(2000);

  while(true) {
    // Read the sensor value
    _force = HTFreadSensor(HTFORCE);

    nxtDisplayClearTextLine(3);
    nxtDisplayClearTextLine(4);
    nxtDisplayTextLine(3, "Force:  %4d", _force);
    wait1Msec(50);
  }
}

/*
 * $Id: hitechnic-force-SMUX-test1.c 133 2013-03-10 15:15:38Z xander $
 */
