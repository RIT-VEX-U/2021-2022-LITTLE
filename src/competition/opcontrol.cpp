#include "competition/opcontrol.h"
#include "robot-config.h"
#include "competition/autonomous.h"
#include "automation.h"
#include <iostream>

void tuning(bool btn)
{
  static bool reset = true;
  if(btn)
  {
    if(reset && tank_drive.turn_to_heading(0, 1))
      reset = false;    
  }else
  {
    tank_drive.reset_auto();
    odom.set_position();
    reset = true;
  }
}

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
  master.ButtonDown.pressed([]() { fork.down(); });
  master.ButtonA.pressed([]() { fork.toggle_clamps(); });
  
  while(true)
  { 
    // ========== DRIVING CONTROLS ==========
    double left_analog = master.Axis3.position() / 100.0;
    double right_analog = master.Axis2.position() / 100.0;

    bool autoaim = master.ButtonL2.pressing() && master.ButtonR2.pressing();

    if(autoaim) {
      drive_with_autoaim(left_analog, right_analog, 2, GoalType::RED);
    }
    else {
      tank_drive.drive_tank(left_analog, right_analog, 2, true);
    }

    // ========== MANIPULATING CONTROLS ==========
    
    if(!autoaim) {
      lift.control(master.ButtonR1.pressing(), master.ButtonR2.pressing(), master.ButtonL2.pressing(), master.ButtonL1.pressing());
    }
    // lift.manual_control(master.ButtonR1.pressing(), master.ButtonR2.pressing(), 
    //   master.ButtonL2.pressing(), master.ButtonL1.pressing());
    
    // ========== SECONDARY REMOTE ==========


    // ========== AUTOMATION ==========

    // std::cout << "LEFT ENCODER:\t" << fork_left.position(rotationUnits::rev) << "\nRIGHT ENCODER:\t" << fork_right.position(rotationUnits::rev) << "\nBOTH:\t" << fork_motors.position(rotationUnits::rev) << "\n\n";
    // printf("raw: %f, rev: %f\n", left_enc.rotation(rotationUnits::raw), left_enc.rotation(rotationUnits::rev));
    // printf("X: %f, Y: %f, Rot: %f\n", odom.get_position().x, odom.get_position().y, odom.get_position().rot);
    
    fflush(stdout);
    fflush(stderr);

    // Wait 20 milliseconds for control loops to calculate time correctly
    vexDelay(20); 
  }

}
