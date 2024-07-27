#include "vex.h"
using namespace vex;


brain Brain;
controller Controller;

motor LF1 = motor(PORT11, ratio18_1, false);
motor LB1 = motor(PORT20, ratio18_1, false);
motor_group LDrive = motor_group(LF1, LB1);


motor RF1 = motor(PORT9, ratio18_1, true);
motor RB1 = motor(PORT3, ratio18_1, true);
motor_group RDrive = motor_group(RF1, RB1);