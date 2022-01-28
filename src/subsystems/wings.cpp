/**
 * File: wings.cpp
 * Author: Dana Colletti
 * Date: 1/20/22
 * Desc:
 *  [insert meaningful desc]
 */

#include "subsystems/wings.h"
#include <iostream>

using namespace vex;

// Constructor
Wings::Wings(digital_out &_wing_deploy, digital_out &_wing_deploy2, digital_out &_clamp):
  wing_deploy(_wing_deploy), wing_deploy2(_wing_deploy2), clamp(_clamp) {}

/**
 * Calls both deployment solenoids to release the wings at the start of a 
 * match
 */
void Wings::deploy() {
  wing_deploy.set(true);
  wing_deploy2.set(true);
  clamp.set(true);
}

/**
 * Fold in the wings, opposite of deploying them
 */
void Wings::undeploy() {
  wing_deploy2.set(false);
  wait(500, timeUnits::msec);
  wing_deploy.set(false);
}

/**
 * Opens the wing clamps
 */
void Wings::clamp_open() {
  clamp.set(false);
}

/**
 * closes the wing clamps
 */
void Wings::clamp_close() {
  std::cout<< "CLAMP CLOSE FUNCTION\n" << fflush(stdout); // DEBUG PRINT, TO BE REMOVED
  clamp.set(true);
}
