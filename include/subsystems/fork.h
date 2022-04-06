#pragma once

#include "vex.h"

using namespace vex;

class Fork {
  public:
  Fork(motor_group &fork_motors, pneumatics &mogo_lock1, pneumatics &mogo_lock2, distance &dist);

  void lift();
  void down();
  void toggle_clamps();
  void hold();
  void stop();

  private:
  motor_group &fork_motors;
  pneumatics  &mogo_lock1;
  pneumatics  &mogo_lock2;
  distance       &dist;

  void open_clamps();
  void close_clamps();
};