#include "subsystems/fork.h"

Fork::Fork(motor_group &fork_motors, pneumatics &mogo_locks, distance &dist, pot &fork_pot):
  fork_motors(fork_motors), mogo_locks(mogo_locks), dist(dist), fork_pot(fork_pot) {
    current_state = UP;
    release_init = true;
  }


// ===== FORK CONTROLS =====

void Fork::lift() {
  // ensure clamps are down
  mogo_locks.open();

  while(fork_pot.angle(rotationUnits::rev) > 0.173) {
    fork_motors.spin(directionType::rev, 100, percentUnits::pct);
  }
  current_state = UP;
  stop();
}

void Fork::down() {
  while(fork_pot.angle(rotationUnits::rev) < 0.692) {
    fork_motors.spin(directionType::fwd, 100, percentUnits::pct);
  }
  current_state = DOWN;
  hold();
}

void Fork::release() {
  mogo_locks.close();
  while(dist.objectDistance(distanceUnits::mm) < 100) {}
  mogo_locks.open();
}

void Fork::toggle_clamps() {
  if(current_state == DOWN) {
    mogo_locks.set(mogo_locks.value() == 0);
  }
}

void Fork::open_clamps() {
  mogo_locks.open();
}

void Fork::hold() {
  fork_motors.stop(brakeType::hold);
  // fork_motors.spin(directionType::fwd, 0.5, percentUnits::pct);
}

void Fork::stop() {
  fork_motors.stop(brakeType::brake);
}

bool Fork::has_goal() {
  return dist.objectDistance(distanceUnits::mm) < 100;
}

Fork::FORK_STATE Fork::get_state() {
  return current_state;
}


////// HELPERS & DEBUGGERS //////

double Fork::get_pot() {
  return fork_pot.angle(rotationUnits::rev);
}
