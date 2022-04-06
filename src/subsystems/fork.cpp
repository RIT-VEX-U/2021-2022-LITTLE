#include "subsystems/fork.h"

Fork::Fork(motor_group &fork_motors, pneumatics &mogo_lock1, pneumatics &mogo_lock2, distance &dist):
  fork_motors(fork_motors), mogo_lock1(mogo_lock1), mogo_lock2(mogo_lock2), dist(dist) {}


// ===== FORK CONTROLS =====

void Fork::lift() {
  while(fork_motors.position(rotationUnits::rev) > 0) {
    fork_motors.spin(directionType::rev, 100, percentUnits::pct);
  }
  stop();
}

void Fork::down() {
  while(fork_motors.position(rotationUnits::rev) < 0.9) {
    fork_motors.spin(directionType::fwd, 100, percentUnits::pct);
  }
  hold();
}

void Fork::toggle_clamps() {
  mogo_lock1.set(mogo_lock1.value() == 0);
  mogo_lock2.set(mogo_lock2.value() == 0);
}

void Fork::hold() {
  fork_motors.stop(brakeType::hold);
  // fork_motors.spin(directionType::fwd, 0.5, percentUnits::pct);
}

void Fork::stop() {
  fork_motors.stop(brakeType::brake);
}


// ===== CLAMP HELPERS =====

void Fork::open_clamps() {
  mogo_lock1.open();
  mogo_lock2.open();
}

void Fork::close_clamps() {
  mogo_lock1.close();
  mogo_lock2.close();
}