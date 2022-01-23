/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\ryan                                             */
/*    Created:      Sun Jan 16 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "robot-config.h"
#include "competition/opcontrol.h"
#include "competition/autonomous.h"

using namespace vex;

competition comp;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  comp.autonomous(Autonomous::autonomous);
  comp.drivercontrol(OpControl::opcontrol);

  while(1) {
    wait(20, timeUnits::msec);
  }
}
