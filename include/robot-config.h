#pragma once

#include "core.h"
#include "subsystems/lift.h"
#include "subsystems/fork.h"

using namespace vex;

// === BRAIN & CONTROLLER ===

extern brain Brain;
extern controller master;


// === DRIVE ===

extern motor_group drive_right;
extern motor fr, mr, br, tr;

extern motor_group drive_left;
extern motor fl, ml, bl, tl;

extern OdometryTank odom;
extern TankDrive tank_drive;


// === LIFT ===

extern motor lift_right, lift_left;
extern pneumatics claw;
extern Lift lift;


// === FORK ===

extern motor fork_right, fork_left;
extern motor_group fork_motors;
extern Fork fork;
extern pneumatics mogo_locks;


// === SENSORS ===

extern inertial imu;
extern rotation lift_sensor;
extern CustomEncoder left_enc, right_enc;
extern distance dist;
extern pot fork_pot;

// NOTE: Vision sensor is declared and initialized in vision_config.h


/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
