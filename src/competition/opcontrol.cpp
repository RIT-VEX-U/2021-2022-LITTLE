#include "competition/opcontrol.h"
#include "robot-config.h"
#include <iostream>

void wings_undeploy() {
  wings.undeploy();
}

/**
 * Contains the main loop of the robot code while running in the driver-control period.
 */
void OpControl::opcontrol() 
{
  // ========== INIT ==========
  
  // honestly not sure what position the wings will be in at the end of auto
  wings.undeploy();
  
  // ========= TESTING ZONE: TO BE REMOVED ==========

  
  // ========= END OF TESTING ZONE ==========


  // ========== LISTENER EVENTS ==========

  // master.ButtonUp.pressed(wings_toggle);

  master.ButtonDown.pressed(wings_undeploy);

  // ========== LOOP ==========
  while(true)
  { 
    // ========== DRIVING CONTROLS ==========
    
    tank_drive.drive_tank(master.Axis3.position() / 100.0, master.Axis2.position() / 100.0);

    // ========== MANIPULATING CONTROLS ==========

    // I know this is deprecated, just bear with me for a minute
    lift.manual_control(master.ButtonR1.pressing(), master.ButtonR2.pressing(), 
      master.ButtonL2.pressing(), master.ButtonL1.pressing());
    
    // ========== SECONDARY REMOTE ==========


    // ========== AUTOMATION ==========

    fflush(stdout);
    fflush(stderr);

    // Wait 20 milliseconds for control loops to calculate time correctly
    vexDelay(20); 
  }

}
