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
  // ========== INIT ==========
  while(imu.isCalibrating()); // do nothing while calibrating
  fork.open_clamps();

  // ========== EVENT LISTENERS ==========
  master.ButtonUp.pressed([]() { fork.lift(); });
  master.ButtonDown.pressed([]() { 
    thread down_t = thread([](){ 
      while(fork_pot.angle(rotationUnits::rev) < 0.692) {
        fork_motors.spin(directionType::fwd, 100, percentUnits::pct);
      }
      fork.hold();
     });
    vexDelay(1000);
    if(!fork.is_down()) {
      down_t.interrupt();
      fork.lift();
    }
  });

  master.ButtonA.pressed([]() {
    thread([]() { fork.release(); });
  });
  
  while(true)
  { 
    // ========== DRIVING CONTROLS ==========
    double left_analog = master.Axis3.position() / 100.0;
    double right_analog = master.Axis2.position() / 100.0;

    bool autoaim = master.ButtonL2.pressing() && master.ButtonR2.pressing();

    if(autoaim) {
      drive_with_autoaim(left_analog, right_analog, 1);
    }
    else {
      tank_drive.drive_tank(left_analog, right_analog, 1, true);
    }

    // ========== MANIPULATING CONTROLS ==========
    
    if(!autoaim) {
      lift.control(master.ButtonR1.pressing(), master.ButtonR2.pressing(), master.ButtonL1.pressing(), master.ButtonL2.pressing());
    }
    
    // ========== SECONDARY REMOTE ==========


    // ========== AUTOMATION ==========

    // Wait 20 milliseconds for control loops to calculate time correctly
    vexDelay(20); 
  }

}
