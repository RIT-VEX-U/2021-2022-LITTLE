/*vex-vision-config:begin*/
#include "vex.h"
vex::vision::signature RED_GOAL = vex::vision::signature (1, 8757, 9633, 9196, -985, -707, -846, 7.9, 0);
vex::vision::signature BLUE_GOAL = vex::vision::signature (2, -2937, -2653, -2796, 10741, 11565, 11154, 9.2, 0);
// value at airbnb
// vex::vision::signature YELLOW_GOAL = vex::vision::signature (3, 247, 2047, 1146, -4839, -4083, -4460, 3, 0);
// value at venue
vex::vision::signature YELLOW_GOAL = vex::vision::signature (3, 2065, 2457, 2262, -3433, -3209, -3322, 6.8, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision vis = vex::vision (vex::PORT1, 46, RED_GOAL, BLUE_GOAL, YELLOW_GOAL, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/