#include "competition/opcontrol.h"
#include "robot-config.h"
#include <iostream>

// Had to declare this here because of annoying VEXcode type parsing :/
void wings_toggle() {
  if(wings.check_open()) {
    wings.clamp_close();
    return;
  }
  wings.clamp_open();
}

void wings_undeploy() {
  wings.undeploy();
}

/**
 * Contains the main loop of the robot code while running in the driver-control period.
 */
void OpControl::opcontrol() 
{
  // ========== INIT ==========
  
  // lift.home();
  //wings.undeploy(); // To be removed before comp, this should happen at the start of auto
  
  // ========= TESTING ZONE: TO BE REMOVED ==========

  while(!master.ButtonA.pressing()) {}
  while(!tank_drive.drive_forward(24.0, 0.5, 0, directionType::fwd)) {
    wait(20, timeUnits::msec);
  }

  // ========= END OF TESTING ZONE ==========


  // ========== LISTENER EVENTS ==========

  master.ButtonL1.pressed(wings_toggle);

  master.ButtonDown.pressed(wings_undeploy);

  // ========== LOOP ==========
  while(true)
  { 
    // ========== DRIVING CONTROLS ==========
    
    tank_drive.drive_tank(master.Axis3.position() / 100.0, master.Axis2.position() / 100.0);

    // ========== MANIPULATING CONTROLS ==========

    // I know this is deprecated, just bear with me for a minute
    lift.manual_control(master.ButtonR1.pressing(), master.ButtonR2.pressing(), 
      master.ButtonA.pressing(), master.ButtonB.pressing());
    
    // ========== SECONDARY REMOTE ==========


    // ========== AUTOMATION ==========

    fflush(stdout);
    fflush(stderr);

    // Wait 20 milliseconds for control loops to calculate time correctly
    vexDelay(20); 
  }

}
