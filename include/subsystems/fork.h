#pragma once

#include "vex.h"

using namespace vex;

class Fork {
  public:
  Fork(motor_group &fork_motors, pneumatics &mogo_locks, distance &dist, pot &fork_pot);

  enum FORK_STATE {
    UP,
    DOWN
  };

  void lift();
  void down();
  void down_with_wait();
  void release();
  void toggle_clamps();
  void open_clamps();
  void close_clamps();
  void hold();
  void stop();
  bool has_goal();
  bool is_down();
  FORK_STATE get_state();

  ////// HELPERS & DEBUGGERS //////

  double get_pot();

  private:
  motor_group &fork_motors;
  pneumatics  &mogo_locks;
  distance    &dist;
  pot         &fork_pot;
  FORK_STATE  current_state;
  bool        release_init;

  static int release_helper(void *dist_p);

};