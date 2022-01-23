/**
 * File: wings.h
 * Author: Dana Colletti
 * Date: 1/20/22
 * Desc:
 *  [insert meaningful desc]
 */

#ifndef _WINGS_H_FILE
#define _WINGS_H_FILE

#include "vex.h"
using namespace vex;

class Wings {
  public:

  // Constructor
  Wings(digital_out wing_deploy, digital_out wing_deploy2, digital_out clamp);

  /**
   * Calls both deployment solenoids to release the wings at the start of a 
   * match
   */
  void deploy();

  /**
   * I realize there is probably a better name for this, but this is what I'm
   * going with for the time being
   */
  void undeploy();

  /**
   * Pretty self-explanatory, but if you're wondering it opens the clamp :)
   */
  void clamp_open();

  void clamp_close();

  bool check_open();

  private:

  digital_out wing_deploy, wing_deploy2, clamp;
  bool is_open;
};

#endif