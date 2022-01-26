#include "competition/autonomous.h"
#include "robot-config.h"
#include <iostream>

/**
 * Contains all the code run during autonomous.
 */ 
void Autonomous::autonomous() 
{
  // ========== INIT ==========

  imu.calibrate();
  while(imu.isCalibrating()) {}

  odom.set_position({.x = 0, .y = 0, .rot = 270});

  drive_left.resetRotation();
  drive_right.resetRotation();
  
  wings.deploy();

  while(!tank_drive.drive_forward(-36, 0.5)) {
    vexDelay(20);
  }

  std::cout<< "EXITED DRIVE LOOP\n" << fflush(stdout);  // this prints

  vexDelay(100);

  // added a tank_drive.turn() here just to make sure it executed, it did

  wings.clamp_close();  // this will not run (runs in opcontrol)

  std::cout<< "ATTEMPTED CLAMP CLOSE" << fflush(stdout);  // does not print

  //tank_drive.drive_forward(36, 0.5);

  // ========== MAIN LOOP ==========
  while(true)
  {

  }

}