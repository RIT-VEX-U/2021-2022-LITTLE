#include "vex.h"
#include "robot-config.h"

using namespace vex;

// === BRAIN & CONTROLLER ===

brain Brain;
controller master;


// === DRIVE ===

motor fr(PORT6, gearSetting::ratio6_1, true), mr(PORT7, gearSetting::ratio6_1, true), 
br(PORT16, gearSetting::ratio6_1, true), tr(PORT17, gearSetting::ratio6_1);
motor_group drive_right(fr, mr, br, tr);

motor fl(PORT5, gearSetting::ratio6_1), ml(PORT4, gearSetting::ratio6_1), 
bl(PORT15, gearSetting::ratio6_1), tl(PORT14, gearSetting::ratio6_1, true);
motor_group drive_left(fl, ml, bl, tl);

robot_specs_t tank_specs = {
  .robot_radius = 7.0,
  .odom_wheel_diam = 2.75,
  .odom_gear_ratio = 1,
  .dist_between_wheels = 8.5,
  .drive_correction_cutoff = 7.0,

  // Driving PID
  .drive_pid={
    .p = 0.7,
    .i = 0,
    .d = 0.00025, 
    .f = 0,
    .k = .1,
    .deadband = 0.2,
    .on_target_time = .1
  },
  // Turning PID
  .turn_pid={
    .p = 0.08, 
    .i = 0,
    .d = 0.005, 
    .f = 0,
    .deadband = 2.0,
    .on_target_time = 0.1
  },
  // WARNING: DUMMY VALUES, TO BE REPLACED
  .correction_pid={
    .p=0.02,
    .d=0.002
  }
};

OdometryTank odom(drive_left, drive_right, tank_specs, &imu, true); // just added the true arg today, did not get to test

TankDrive tank_drive(drive_left, drive_right, tank_specs, &odom);


// === LIFT ===

motor lift_right(PORT10, gearSetting::ratio18_1), lift_left(PORT1, gearSetting::ratio18_1, true);
motor_group lift_motors(lift_left, lift_right);
pneumatics claw(Brain.ThreeWirePort.E);

// WARNING: DUMMY VALUES, TO BE REPLACED
PID::pid_config_t lift_pid = {
  .p = 300,
  .i = 0,
  // .d = 60,
  .f = 0,
  .deadband = 0.5,
  .on_target_time = 0.1
};

rotation lift_sensor(PORT9);

Lift lift(lift_motors, lift_sensor, claw, lift_pid);


// === SENSORS ===

inertial imu(PORT2);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  imu.calibrate();

  // Nothing to initialize
}