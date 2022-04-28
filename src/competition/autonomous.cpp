#include "competition/autonomous.h"
#include "robot-config.h"
#include "automation.h"
#include <iostream>

#define OPP_ZONE 96
#define DISCREPANCY 25
#define MID_LINE 72

const position_t robot_start = {
  .x = 108,
  .y = 17,
  .rot = 270
};

const position_t center_goal_start = {
  .x = 72,
  .y = 72,
  .rot = 0
};

/**
 * Currently aims for the goal immediately in front of the robot
 */
void rush_auto() {
  odom.set_position(robot_start);

  GenericAuto rush;

  // init stuff
  rush.add([](){ 
    fork.down(); 
    fork.open_clamps();
    return true; 
  });

  // driving to the goal
  rush.add([](){ 
    // TODO: clean this up
    while(!drive_to_goal(1.0, [](){ return fork.has_goal(); }, BLUE/*, YELLOW*/) && odom.get_position().y < OPP_ZONE - DISCREPANCY) {  // please don't ask me where this number comes from
      vexDelay(20);
    }
    tank_drive.stop(brakeType::brake);
    return true;
  });

  // delay to make sure clamps are secure
  rush.add_delay(500);

  // rush.add([](){ 
  //   if(!fork.has_goal()) {
  //     // turn away from opp zone
  //     tank_drive.turn_to_heading(180, 0.5);

  //     // searching for center goal
  //     while(!tank_drive.turn_degrees(5, 0.15) && !sees_goal(BLUE/*YELLOW*/)) {
  //       vexDelay(20);
  //     }

  //     if(sees_goal(BLUE /*YELLOW*/)) {
  //       // TODO: center the robot around the goal

  //       while(!drive_to_goal(1.0, [](){ return fork.has_goal(); }, BLUE/*YELLOW*/) && odom.get_position().y > 48) {
  //         vexDelay(20);
  //       }
  //     }
  //   }
  //   return true;
  // });

  // driving back to home zone
  // rush.add([](){ return tank_drive.drive_to_point(108, 20, 1.0, 0.0); });

  rush.add([](){
    double dist_from_mid = odom.get_position().y - (MID_LINE - DISCREPANCY);
    
    fflush(stdout);

    double head = 165 + (dist_from_mid);

    fork.lift();

    while(!tank_drive.turn_to_heading(head, 1.0)) {
      vexDelay(20);
    }

    // while(true) {
    //   printf("ODOM X,Y: %f,%f\n", odom.get_position().x, odom.get_position().y);
    // }

    return true;
  });

  rush.add([](){
    while(!tank_drive.drive_to_point(82, 69, 0.5, 0.5)) {
      vexDelay(20);
    }

    return true;
  });

  rush.add_delay(2000);

  rush.add([](){
    claw.open();
    return true;
  });

  rush.add_delay(2000);

  rush.add([](){
    lift.set_lift_height(Lift::DRIVING);
    while(!tank_drive.drive_to_point(20, 20, 0.5, 0.5)) {
      vexDelay(20);
    }
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

  // drive_left.resetRotation();
  // drive_right.resetRotation();
  
  // match();
  // skills();
  rush_auto();

  // ========== MAIN LOOP ==========
  // while(true)
  // {

  // }

}