#include "competition/opcontrol.h"
#include "robot-config.h"
#include "competition/autonomous.h"
#include <iostream>

void wings_undeploy() {
  wings.undeploy();
}

/**
 * Contains the main loop of the robot code while running in the driver-control period.
 */
void OpControl::opcontrol() 
{
  Autonomous::autonomous();
  // ========== INIT ==========
  while(imu.isCalibrating()); // do nothing while calibrating
  
  // honestly not sure what position the wings will be in at the end of auto
  wings.undeploy();
  
  // ========= TESTING ZONE: TO BE REMOVED ==========

  // odom.set_position();
  // GenericAuto a;
  // a.add([](){return tank_drive.drive_to_point(24, 24, .5, 1);});
  // // a.add([](){return tank_drive.turn_to_heading(0, 1);});

  // if(!master.ButtonDown.pressing())
  //   a.run(true);

  
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
    lift.control(master.ButtonR1.pressing(), master.ButtonR2.pressing(), master.ButtonL2.pressing(), master.ButtonL1.pressing());
    // lift.manual_control(master.ButtonR1.pressing(), master.ButtonR2.pressing(), 
    //   master.ButtonL2.pressing(), master.ButtonL1.pressing());
    
    // ========== SECONDARY REMOTE ==========


    // ========== AUTOMATION ==========

    fflush(stdout);
    fflush(stderr);

    // Wait 20 milliseconds for control loops to calculate time correctly
    vexDelay(20); 
  }

}
