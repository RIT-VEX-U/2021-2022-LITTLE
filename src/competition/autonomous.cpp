#include "competition/autonomous.h"
#include "robot-config.h"
#include <iostream>

void match() {
  odom.set_position({.x = 0, .y = 0, .rot = 270});
  wings.deploy();

  while(!tank_drive.drive_forward(-33, 0.5)) {
    vexDelay(20);
  }

  wings.clamp.set(false);

  vexDelay(100);

  while(!tank_drive.drive_forward(32, 0.5)) {
    vexDelay(20);
  }
}

void skills() {
  // wait for big to be out of the way
  wait(27, timeUnits::sec);
}

/**
 * Contains all the code run during autonomous.
 */ 
void Autonomous::autonomous() 
{
  // ========== INIT ==========

  imu.calibrate();
  while(imu.isCalibrating()) {}

  drive_left.resetRotation();
  drive_right.resetRotation();
  
  match();

  // ========== MAIN LOOP ==========
  while(true)
  {

  }

}