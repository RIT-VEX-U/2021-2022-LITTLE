#pragma once

#include "vex.h"

using namespace vex;

class Fork {
  public:
  Fork(motor_group &fork_motors, pneumatics &mogo_locks, distance &dist);

  void lift();
  void down();
  void toggle_clamps();
  void hold();
  void stop();

  enum FORK_STATE {
    UP,
    DOWN
  };

  private:
  motor_group &fork_motors;
  pneumatics  &mogo_locks;
  distance    &dist;
  FORK_STATE  current_state;

  FORK_STATE get_state();
};