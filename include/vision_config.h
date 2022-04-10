/*vex-vision-config:begin*/
#include "vex.h"
vex::vision::signature RED_GOAL = vex::vision::signature (1, 8757, 9633, 9196, -985, -707, -846, 7.9, 0);
vex::vision::signature BLUE_GOAL = vex::vision::signature (2, -2937, -2653, -2796, 10741, 11565, 11154, 9.2, 0);
vex::vision::signature YELLOW_GOAL = vex::vision::signature (3, 473, 1945, 1210, -4897, -4763, -4830, 8.3, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision vis = vex::vision (vex::PORT8, 50, RED_GOAL, BLUE_GOAL, YELLOW_GOAL, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/