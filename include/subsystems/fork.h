#pragma once

#include "vex.h"

using namespace vex;

class Fork {
  public:
  Fork(motor_group &fork_motors, pneumatics &mogo_locks, distance &dist);

  enum FORK_STATE {
    UP,
    DOWN
  };

  void lift();
  void down();
  void release();
  void toggle_clamps();
  void open_clamps();
  void hold();
  void stop();
  FORK_STATE get_state();

  private:
  motor_group &fork_motors;
  pneumatics  &mogo_locks;
  distance    &dist;
  FORK_STATE  current_state;
  bool        release_init;

  static int release_helper(void *dist_p);
};