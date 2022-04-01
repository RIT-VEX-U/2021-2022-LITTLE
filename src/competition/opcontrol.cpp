#include "competition/opcontrol.h"
#include "robot-config.h"
#include "competition/autonomous.h"
#include <iostream>

/**
 * Contains the main loop of the robot code while running in the driver-control period.
 */
void OpControl::opcontrol() 
{
  // Autonomous::autonomous();
  // ========== INIT ==========
  while(imu.isCalibrating()); // do nothing while calibrating

  // ========== EVENT LISTENERS ==========
  master.ButtonUp.pressed([]() { fork.lift(); });
  master.ButtonDown.pressed([]() { fork.place(); });
  
  while(true)
  { 
    // ========== DRIVING CONTROLS ==========
    
    tank_drive.drive_tank(master.Axis3.position() / 100.0, master.Axis2.position() / 100.0, true);

    // ========== MANIPULATING CONTROLS ==========
    
    lift.control(master.ButtonR1.pressing(), master.ButtonR2.pressing(), master.ButtonL2.pressing(), master.ButtonL1.pressing());
    // lift.manual_control(master.ButtonR1.pressing(), master.ButtonR2.pressing(), 
    //   master.ButtonL2.pressing(), master.ButtonL1.pressing());
    
    // ========== SECONDARY REMOTE ==========


    // ========== AUTOMATION ==========

    std::cout << "LEFT ENCODER:\t" << fork_left.position(rotationUnits::rev) << "\nRIGHT ENCODER:\t" << fork_right.position(rotationUnits::rev) << "\nBOTH:\t" << fork_motors.position(rotationUnits::rev) << "\n\n";

    fflush(stdout);
    fflush(stderr);

    // Wait 20 milliseconds for control loops to calculate time correctly
    vexDelay(20); 
  }

}
