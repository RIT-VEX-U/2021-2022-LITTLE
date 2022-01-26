#pragma once

#include "core.h"
#include "subsystems/wings.h"
#include "subsystems/lift.h"

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


// === WINGS ===

extern Wings wings;
extern digital_out wing_deploy;
extern digital_out wing_deploy2;
extern digital_out wing_clamp;

// === SENSORS ===

extern inertial imu;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
