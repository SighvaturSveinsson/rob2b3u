#include "robot-config.h" 
/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
This program instructs your robot to use remote control values to move the robot.

Robot Configuration: 
[Smart Port] [Name] [Type] [Description] [Reversed] 
Motor Port 11 LeftMotor V5 Smart Motor Left side motor false 
Motor Port 20 RightMotor V5 Smart Motor Right side motor true 
Motor Port 18 ArmMotor V5 Smart Motor Arm motor false 
Motor Port 16 ClawMotor V5 Smart Motor Claw motor false
Motor Port 17 TurnTableMotor V5 Smart Motor Turntable motor false

----------------------------------------------------------------------------------------------------*/

int main() {

  //Display that the program has started to the screen.
  Brain.Screen.print("Controller Program Started");

  //Use these variables to set the speed of the arm and claw.
  int armSpeedPCT = 20;
  int clawSpeedPCT = 20;

  //Create an infinite loop so that the program can pull remote control values every iteration.
  //This loop causes the program to run forever.
  while(1) {
      //Drive Control
      //Set the left and right motor to spin forward using the controller Axis values as the velocity value.
      //Since we are using a single joystick, we will need to calculate the final volicity for each motor.
      LeftMotor.spin(vex::directionType::fwd, (Controller1.Axis3.value() + Controller1.Axis4.value())/6, vex::velocityUnits::pct); //(Axis3+Axis4)/2
      RightMotor.spin(vex::directionType::fwd, (Controller1.Axis3.value() - Controller1.Axis4.value())/6, vex::velocityUnits::pct);//(Axis3-Axis4)/2

      //Turntable Control
      if(Controller1.ButtonA.pressing()) { //If the A button is pressed...
          //...Spin the turntable motor right.
          TurnTableMotor.spin(vex::directionType::fwd, armSpeedPCT, vex::velocityUnits::pct);
      }
      else if(Controller1.ButtonY.pressing()) { //If the Y button is pressed...
          //...Spin the turntable motor left.
          TurnTableMotor.spin(vex::directionType::rev, armSpeedPCT, vex::velocityUnits::pct);
      }
      else { //If the the A or Y button is not pressed...
          //...Stop the turntable motor.
          TurnTableMotor.stop(vex::brakeType::brake);
      }

      //Arm Control
      if(Controller1.ButtonUp.pressing()) { //If button up is pressed...
          //...Spin the arm motor forward.
          ArmMotor.spin(vex::directionType::fwd, armSpeedPCT, vex::velocityUnits::pct);
      }
      else if(Controller1.ButtonDown.pressing()) { //If the down button is pressed...
          //...Spin the arm motor backward.
          ArmMotor.spin(vex::directionType::rev, armSpeedPCT, vex::velocityUnits::pct);
      }
      else { //If the the up or down button is not pressed...
          //...Hold the arm motor so that it does not drop.
          ArmMotor.stop(vex::brakeType::hold);
      }

      //Claw Control
      if(Controller1.ButtonX.pressing()) { //If the B button is pressed...
          //...Spin the claw motor forward.
          ClawMotor.spin(vex::directionType::fwd, clawSpeedPCT, vex::velocityUnits::pct);
      }
      else if(Controller1.ButtonB.pressing()) { //If the X button is pressed...
          //...Spin the claw motor backward.
          ClawMotor.spin(vex::directionType::rev, clawSpeedPCT, vex::velocityUnits::pct);
      }
      else { //If the x or B button are not pressed...        
          //...Stop the claw motor.
          ClawMotor.stop(vex::brakeType::brake);        
      }

    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources.
  }
}
