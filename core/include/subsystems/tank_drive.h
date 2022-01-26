#pragma once

#ifndef PI
#define PI 3.141592654
#endif

#include "vex.h"
#include "../core/include/utils/pid.h"
#include "../core/include/subsystems/odometry/odometry_tank.h"
#include "../core/include/robot_specs.h"
#include <vector>
#include "../core/src/utils/pure_pursuit.cpp"

using namespace vex;

class TankDrive
{
public:

  /**
   * Create the TankDrive object 
   */
  TankDrive(motor_group &left_motors, motor_group &right_motors, robot_specs_t &config, OdometryTank *odom=NULL);

  /**
   * Stops rotation of all the motors using their "brake mode"
   */
  void stop();

  /**
   * Drive the robot using differential style controls. left_motors controls the left motors,
   * right_motors controls the right motors.
   * 
   * left_motors and right_motors are in "percent": -1.0 -> 1.0
   */
  void drive_tank(double left, double right, int power=1);

  /**
   * Drive the robot using arcade style controls. forward_back controls the linear motion,
   * left_right controls the turning.
   * 
   * left_motors and right_motors are in "percent": -1.0 -> 1.0
   */
  void drive_arcade(double forward_back, double left_right, int power=1);

  /**
   * Autonomously drive forward or backwards, X inches infront or behind the robot's current position.
   * This driving method is relative, so excessive use may cause the robot to get off course!
   *
   * @param inches Distance to drive in a straight line
   * @param speed How fast the robot should travel, 0 -> 1.0
   * @param correction How much the robot should correct for being off angle
   * @param dir Whether the robot is travelling forwards or backwards
   */
  // bool drive_forward(double inches, double speed, double correction, directionType dir);

  bool drive_forward(double inches, double speed);

  /**
   * Autonomously turn the robot X degrees to the right (negative for left), with a maximum motor speed
   * of percent_speed (-1.0 -> 1.0)
   * 
   * Uses a PID loop for it's control.
   */
  bool turn_degrees(double degrees, double percent_speed);

  /**
   * Use odometry to automatically drive the robot to a point on the field.
   * X and Y is the final point we want the robot.
   */
  bool drive_to_point(double x, double y, double speed, double correction_speed, vex::directionType direction=vex::directionType::fwd);

  /**
   * Turn the robot in place to an exact heading relative to the field.
   * 0 is forward, and 0->360 is clockwise.
   */
  bool turn_to_heading(double heading_deg, double speed);

  /**
   * Reset the initialization for autonomous drive functions
   */
  void reset_auto();

  static double modify_inputs(double input, int power=2);

  bool pure_pursuit(std::vector<PurePursuit::hermite_point> path, double radius, double speed, double res);

private:
  motor_group &left_motors;
  motor_group &right_motors;

  PID drive_pid;
  PID turn_pid;
  PID correction_pid;

  OdometryTank *odometry;

  position_t saved_pos;

  robot_specs_t &config;

  bool func_initialized = false;
};
