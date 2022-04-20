#include "automation.h"
#include "vision_config.h"

/**
 * Helper to find the x-coordinate of nearest given color goal
 */
double vision_x_dist(GoalType color) {
  switch(color) {
    case RED:
      vis.takeSnapshot(RED_GOAL);
      break;
    case BLUE:
      vis.takeSnapshot(BLUE_GOAL);
      break;
    case YELLOW:
      vis.takeSnapshot(YELLOW_GOAL);
      break;
    case ANY:
    default:
      vis.takeSnapshot(0,10);
  }

  vex::vision::object largest = vis.largestObject;
  double dist_from_center = 0;

  // if object is not large enough to be a goal
  if(largest.height * largest.width > 800) {
    dist_from_center = largest.centerX - (VIEW_WIDTH/2);
  }

  return dist_from_center;
}

bool drive_to_goal(double speed, bool (*end_condition) (void), GoalType color) {
  // PID tuning only used here
  static PID::pid_config_t pid_cfg = {
    .p = .003,
    .d = 0
  };
  static PID pid(pid_cfg);

  pid.update(vision_x_dist(color));
  tank_drive.drive_tank(-speed - pid.get(), -speed + pid.get());

  if(end_condition())
  {
    tank_drive.stop();
    return true;
  }

  return false;
}

void drive_with_autoaim(double left, double right, int power, GoalType color) {
  static PID::pid_config_t pid_cfg = {
    .p = .004
  };
  static PID pid(pid_cfg);

  pid.update(vision_x_dist(color));
  tank_drive.drive_tank(left - pid.get() - .5, right + pid.get() - .5, power);
}