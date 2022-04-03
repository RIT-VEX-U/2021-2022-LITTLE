#pragma once

#include "vex.h"

using namespace vex;

class Fork {
  public:
  Fork(motor_group &fork_motors, pneumatics &mogo_lock1, pneumatics &mogo_lock2, limit &lim);

  void lift();
  void place();
  void hold();
  void stop();

  private:
  motor_group &fork_motors;
  pneumatics  &mogo_lock1;
  pneumatics  &mogo_lock2;
  limit       &lim;
};