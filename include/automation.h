#pragma once
#include "robot-config.h"

#define VIEW_WIDTH 320  // vision sensor's field of view is 320 pixels across

enum GoalType {
  RED,
  BLUE,
  YELLOW,
  ANY
};

bool drive_to_goal(double speed, bool (*end_condition) (void), GoalType color=ANY);
void drive_with_autoaim(double left, double right, int power, GoalType color=ANY);