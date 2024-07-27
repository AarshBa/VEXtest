/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Aarsh                                                     */
/*    Created:      5/20/2024, 10:24:07 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

//Settings
double kP = 0.0;
double kI = 0.0;
double kD = 0.0;


// Autonomous Settings
int desiredValue = 200;
int desiredTurnValue = 0;

int error; // Sensored Val - Desired Val : Positional value    What you have currently minus what you want 
int prevError = 0; // Position 20 miliseconds ago
int derivative; // error - prevError = speed
int totalError= 0; // totalError += error



bool enableDrivePID = true;

int drivePID() {
  while (enableDrivePID) {

    int leftDrivePosition = LDrive.position(degrees);
    int rightDrivePosition = RDrive.position(degrees);

    //gets average of all drive motors
    int averagePosition = (leftDrivePosition + rightDrivePosition)/2;

    // Potential
    error = averagePosition - desiredValue;

    // Derivative
    derivative = error - prevError;

    // Integral
    totalError += error;

    double lateralMotorPower = (error * kP + derivative * kD + totalError * kI);




    prevError = error;
    vex::task::sleep(20);

  }

  return 1;
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/



void autonomous(void) {

  vex::task auton(drivePID);

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {

  while (1) {
    drivetrain Robot = drivetrain(LDrive, RDrive, 4*3.14, 5.5, 12, inches, 1);
    Robot.driveFor(24, inches);
    Robot.turnFor(180, degrees);

    LDrive.spin(forward, Controller.Axis2.position() + Controller.Axis1.position(), pct);
    RDrive.spin(forward, Controller.Axis2.position() - Controller.Axis1.position(), pct);


        if (Controller.Axis3.position()==0) {
            LDrive.stop(coast);
            RDrive.stop(coast);
        } else {
            LDrive.spin(forward, Controller.Axis2.position() + Controller.Axis1.position(), pct);
            RDrive.spin(forward, Controller.Axis2.position() - Controller.Axis1.position(), pct);
        }
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
}
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
