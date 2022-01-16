#include "competition/opcontrol.h"
#include "robot-config.h"

/**
 * Contains the main loop of the robot code while running in the driver-control period.
 */
void OpControl::opcontrol() 
{
  // ========== INIT ==========
  
  // ========== LOOP ==========
  while(true)
  {
    // ========== DRIVING CONTROLS ==========
    

    // ========== MANIPULATING CONTROLS ==========

    
    // ========== SECONDARY REMOTE ==========


    // ========== AUTOMATION ==========

    fflush(stdout);
    fflush(stderr);

    // Wait 20 milliseconds for control loops to calculate time correctly
    vexDelay(20); 
  }

}
