#include "vex.h"
#include "robot-config.h"

using namespace vex;

// === BRAIN & CONTROLLER ===

brain Brain;
controller master;


// === DRIVE ===
// TODO: check directions
motor fr(PORT6, gearSetting::ratio6_1, true), mr(PORT19, gearSetting::ratio6_1, true), 
br(PORT17, gearSetting::ratio6_1, true), tr(PORT20, gearSetting::ratio6_1);
motor_group drive_right(fr, mr, br, tr);

motor fl(PORT5, gearSetting::ratio6_1), ml(PORT12, gearSetting::ratio6_1), 
bl(PORT14, gearSetting::ratio6_1), tl(PORT11, gearSetting::ratio6_1, true);
motor_group drive_left(fl, ml, bl, tl);

// TODO: probably check all of this lol uh oh
robot_specs_t tank_specs = {
  .robot_radius = 7.5,
  .odom_wheel_diam = 2.75,
  .odom_gear_ratio = 1,
  .dist_between_wheels = 8.5,
  .drive_correction_cutoff = 7.0,

  // Driving PID
  .drive_pid={
    .p = 0.1,
    .i = 0.01,
    .d = 0.01, 
    // .f = 0,
    // .k = .1,
    .deadband = 1.5,
    .on_target_time = .1
  },
  // Turning PID
  .turn_pid={
    .p = 0.03, 
    .i = 0.01,
    .d = 0.002, 
    // .f = 0,
    .deadband = 5.0,
    .on_target_time = 0.1
  },
  // WARNING: DUMMY VALUES, TO BE REPLACED
  .correction_pid={
    .p=0.05,
    .d=0.01
  }
};

OdometryTank odom(left_enc, right_enc, tank_specs, &imu, true); // just added the true arg today, did not get to test

TankDrive tank_drive(drive_left, drive_right, tank_specs, &odom);


// === LIFT ===

motor lift_right(PORT10, gearSetting::ratio18_1), lift_left(PORT1, gearSetting::ratio18_1, true);
motor_group lift_motors(lift_left, lift_right);
pneumatics claw(Brain.ThreeWirePort.H);

// TODO: these are probably fine, but test anyway
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


// === FORK ===

motor fork_left(PORT15, true), fork_right(PORT16);
motor_group fork_motors(fork_left, fork_right);
limit lim(Brain.ThreeWirePort.E);
pneumatics mogo_lock1(Brain.ThreeWirePort.F), mogo_lock2(Brain.ThreeWirePort.G);
Fork fork(fork_motors, mogo_lock1, mogo_lock2, lim);


// === SENSORS ===

// TODO: steal Nemo's IMU (sorry, Nemo)
inertial imu(PORT2);

// NOTE: the VEX API assumes an encoder occupies two adjacent ports, always provide the "earlier" port
CustomEncoder left_enc(Brain.ThreeWirePort.A, 2048);  // ports A & B
CustomEncoder right_enc(Brain.ThreeWirePort.C, 2048); // ports C & D

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  imu.calibrate();

  // Nothing to initialize
}