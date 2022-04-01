#include "subsystems/fork.h"

Fork::Fork(motor_group &fork_motors, pneumatics &mogo_lock1, pneumatics &mogo_lock2, limit &lim):
  fork_motors(fork_motors), mogo_lock1(mogo_lock1), mogo_lock2(mogo_lock2), lim(lim) {}

void Fork::lift() {
  while(fork_motors.position(rotationUnits::rev) > 0) {
    fork_motors.spin(directionType::rev, 100, percentUnits::pct);
  }
  stop();
}

void Fork::place() {
  while(fork_motors.position(rotationUnits::rev) < 0.92) {
    fork_motors.spin(directionType::fwd, 100, percentUnits::pct);
  }
  stop();
}

void Fork::stop() {
  fork_motors.stop();
}