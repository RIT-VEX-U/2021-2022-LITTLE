#include "competition/autonomous.h"
#include "robot-config.h"
#include "automation.h"

#define OPP_ZONE 68//96 // the distance to the opposing team's home zone,
#define DISCREPANCY 25
// #define MID_LINE 72

const position_t robot_start = {
  .x = 108,
  .y = 17,
  .rot = 270
};

bool fork_has_goal() { return fork.has_goal(); }

/**
 * Currently aims for the goal immediately in front of the robot
 */
void rush_auto() {
  odom.set_position(robot_start);

  GenericAuto rush;

  // init stuff
  rush.add([](){ 
    fork.open_clamps();
    return true; 
  });

  // bring the fork down while driving forward
  rush.add_async([](){ 
    fork.down();
    return true;
  });

  // driving to the goal
  rush.add([](){ 
    // stop either when the goal is in the fork or the robot is about to cross into the other home zone
    while(!drive_to_goal(1.0, fork_has_goal, YELLOW) && odom.get_position().y < OPP_ZONE - DISCREPANCY) {
      vexDelay(20);
    }
    printf("autonomous.cpp: ODOM Y: %f\n", odom.get_position().y);
    tank_drive.stop(brakeType::brake);  // don't let the robot roll into the other home zone

    if(odom.get_position().x >= OPP_ZONE - DISCREPANCY) {
      tank_drive.drive_tank(0.5, 0.5);
      fork.open_clamps();
      tank_drive.stop();
    }
    return true;
  });

  // delay to make sure clamps are secure
  rush.add_delay(500);

  
  rush.add([](){
    while(!tank_drive.drive_to_point(odom.get_position().x, 48 - DISCREPANCY, 1.0, 0.0)) {
      vexDelay(20);
    }

    return true;
  });

  // let the robot settle before lifting mogo
  rush.add_delay(500);

  rush.add([]() {
    fork.lift();
    return true;
  });

  // drive to center goal
  rush.add([](){
    claw.close();

    while(!tank_drive.drive_to_point(85, 63, 0.5, 0.5)) {
      vexDelay(20);
    }

    while(!tank_drive.drive_to_point(88, 68, 0.2, 0.1)) {
      vexDelay(20);
    }

    return true;
  });

  // grab center goal
  rush.add_delay(500);
  rush.add([](){
    claw.open();
    return true;
  });


  rush.add_delay(500);
  rush.add([](){
    while(!tank_drive.turn_to_heading(180, 0.5)) {
      vexDelay(20);
    }
    return true;
  });

  rush.add([](){
    lift.set_lift_height(Lift::DRIVING);
    lift.set_lift_height(Lift::DOWN);
    return true;
  });

  // wait for 24
  rush.add_delay(12000);

  // drive back to home zone
  rush.add_delay(500);
  rush.add([](){
    lift.set_lift_height(Lift::DRIVING);
    while(!tank_drive.drive_to_point(25, 25, 0.5, 0.5)) {
      vexDelay(20);
    }
    return true;
  });

  rush.add([](){
    fork.close_clamps();
    return true;
  });

  rush.run(true);
}

void match() {
  odom.set_position({.x = 0, .y = 0, .rot = 270});
  // wings.deploy();

  while(!tank_drive.drive_forward(-33, 0.5, 1, directionType::rev)) {
    vexDelay(20);
  }

  // wings.clamp.set(false);

  vexDelay(100);

  while(!tank_drive.drive_forward(32, 0.5, 1, directionType::fwd)) {
    vexDelay(20);
  }
}

/**
 * Skills autonomous program
 */
void skills() {
  // wait for big to be out of the way
  // wait(27, timeUnits::sec);

  static timer tmr;

  odom.set_position({.x=106, .y=17, .rot=90});

  static state_ptr halfdelay = [](){
    vexDelay(500);
    return true;
  };

  task odom_reporting([](){
     while(true)
    {
      position_t pos = odom.get_position();
      printf("X: %f; Y: %f; ROT: %f\n", pos.x, pos.y, pos.rot);
      vexDelay(20);
    }

    return 0;
  });

  GenericAuto a;
  a.add([](){lift.set_lift_height(Lift::DRIVING); return halfdelay();});
  a.add([](){lift.set_lift_height(Lift::DOWN); return halfdelay();});
  a.add([](){claw.open();return tank_drive.drive_to_point(106, 61, .3, 1);});
  a.add([](){claw.close(); return halfdelay();});

  // Drive backwards and open the claw at a set distance from the end
  a.add([](){
    task t([]()
    {
      while(OdometryBase::pos_diff({.x=106, .y=17}, odom.get_position()) > 12) {vexDelay(50);}
      claw.open();
      return 0;
    });
    return true;
  });
  a.add([](){return tank_drive.drive_to_point(106, 17, .3, 1, directionType::rev);});

  // Go for the alliance goal
  a.add([](){return tank_drive.turn_to_heading(38, .5);});
  a.add([](){return tank_drive.drive_to_point(120, 29, .2, 1);});
  a.add([](){claw.close(); return halfdelay();});
  a.add([](){return tank_drive.turn_to_heading(90, .5);});
  a.add([](){
    wait(30 - tmr.time(sec), sec);
    return true;
  });
  a.add([](){return tank_drive.drive_to_point(120, 100, .4, 1);});
  a.add([](){claw.open(); return halfdelay();});
  a.add([](){return tank_drive.drive_to_point(120, 88, .3, 1, directionType::rev);});
  a.run(true);

  // while(true)
  // {
  //   position_t pos = odom.get_position();
  //   printf("X: %f; Y: %f; ROT: %f\n", pos.x, pos.y, pos.rot);
  //   vexDelay(20);
  // }

}

/**
 * Qualifier autonomous to guarentee an auto win point
 */
void qual()
{
  task odom_reporting([](){
     while(true)
    {
      position_t pos = odom.get_position();
      printf("X: %f; Y: %f; ROT: %f\n", pos.x, pos.y, pos.rot);
      vexDelay(20);
    }

    return 0;
  });

  odom.set_position({.x=129, .y=17, .rot=90});

  GenericAuto a;
  // Drive forward slowly and deposit a ring in the goal, and flip out the claw mech
  a.add([](){return tank_drive.drive_to_point(129, 21.5, .15, 1);});
  a.add([](){
    claw.open();
    // wings.undeploy();
    vexDelay(300);
    lift.set_lift_height(Lift::DRIVING);
    vexDelay(200);
    lift.set_lift_height(Lift::DOWN);
    return true;
    });
  // back up slightly, and drive forward and grab the goal, move it off the line
  a.add([](){return tank_drive.drive_to_point(129, 19, .2, 1, directionType::rev);});
  a.add([](){return tank_drive.drive_to_point(129, 24, .2, 1);});
  a.add([](){claw.close(); vexDelay(100); return true;});
  a.add([](){return tank_drive.turn_to_heading(135, .5);});
  
  a.run(true);
  
  while(true){
    vexDelay(50);
  }



}

/**
 * Contains all the code run during autonomous.
 */ 
void Autonomous::autonomous() 
{
  // ========== INIT ==========

  // imu.calibrate(); - done in init
  while(imu.isCalibrating()) {}
  
  // match();
  // skills();
  rush_auto();
}