/*
 * @Author: ELEGOO
 * @Date: 2019-10-22 11:59:09
 * @LastEditTime: 2020-12-18 14:14:35
 * @LastEditors: Changhua
 * @Description: Smart Robot Car V4.0
 * @FilePath: 
 */
#include <avr/wdt.h>
#include "DeviceDriverSet_xxx0.h"
#include "ApplicationFunctionSet_xxx0.h"
#include "DeviceDriverSet_xxx0.h"
#include <Time.h>


/* Robot Motion
  Forward,       //(1)
  Backward,      //(2)
  Left,          //(3)
  Right,         //(4)
  LeftForward,   //(5)
  LeftBackward,  //(6)
  RightForward,  //(7)
  RightBackward, //(8)
  stop_it        //(9)
*/   

//*********************
// IR Controller Object
uint8_t IRrecv_button;
// create an object
DeviceDriverSet_IRrecv AppIRrecv1;
// fucntion to read the code for the pressed button
 int ReadRemote (){
	AppIRrecv1.DeviceDriverSet_IRrecv_Get(&IRrecv_button);
  return IRrecv_button-5 ;
} 



//LED color definition
uint32_t Color(uint8_t r, uint8_t g, uint8_t b)
{
return (((uint32_t)r << 16) | ((uint32_t)g << 8) | b);
}


void myColor(int Red, int Green, int Blue, int Intensity)
{
   FastLED.setBrightness(Intensity);
   FastLED.showColor(Color(Red, Green, Blue));
}







// infraRed Line Follower
DeviceDriverSet_ITR20001 AppITR20001A ;
 int TrackingData_R,TrackingData_M,TrackingData_L ;
  int infraRed_R(){
    return AppITR20001A.DeviceDriverSet_ITR20001_getAnaloguexxx_R() ;
  }

    int infraRed_M(){
    return AppITR20001A.DeviceDriverSet_ITR20001_getAnaloguexxx_M() ;
  }

    int infraRed_L(){
    return AppITR20001A.DeviceDriverSet_ITR20001_getAnaloguexxx_L() ;
  }
   
  



//motionControl
void ApplicationFunctionSet_SmartRobotCarMotionControl(SmartRobotCarMotionControl direction, uint8_t is_speed);
const auto& move = ApplicationFunctionSet_SmartRobotCarMotionControl;



//Servo - Ultrasonic sensor position
 DeviceDriverSet_Servo AppServo1;
 void servoControl (unsigned int Position_angle){
	AppServo1.DeviceDriverSet_Servo_control(Position_angle);
} 

DeviceDriverSet_Servo AppServo2;
 void servo2Control (unsigned int Position_angle2){
	AppServo2.DeviceDriverSet_Servo_control(Position_angle2);
} 

 //ULTRASONIC;
 DeviceDriverSet_ULTRASONIC AppULTRASONIC1;
 uint16_t get_Distance;
 void readUltrasonicSensor(uint16_t &get_Distance){
         AppULTRASONIC1.DeviceDriverSet_ULTRASONIC_Get(&get_Distance /*out*/);
  }


void Init()
{
 Application_FunctionSet.ApplicationFunctionSet_Init();
 Serial.begin(9600);
 AppITR20001A.DeviceDriverSet_ITR20001_Init();

}

static boolean
function_xxx(long x, long s, long e) //f(x)
{
  if (s <= x && x <= e)
    return true;
  else
    return false;
}
 

 enum SmartRobotCarFunctionalModel
{
  Standby_mode,           /*Standby Mode*/
  TraceBased_mode,        /*Line Tracking Mode*/
  ObstacleAvoidance_mode, /*Obstacle Avoidance Mode*/
  Follow_mode,            /*Following Mode*/
  Rocker_mode,            /*Rocker Control Mode*/
  CMD_inspect,
  CMD_Programming_mode,                   /*Programming Mode*/
  CMD_ClearAllFunctions_Standby_mode,     /*Clear All Functions And Enter Standby Mode*/
  CMD_ClearAllFunctions_Programming_mode, /*Clear All Functions And Enter Programming Mode*/
  CMD_MotorControl,                       /*Motor Control Mode*/
  CMD_CarControl_TimeLimit,               /*Car Movement Direction Control With Time Limit*/
  CMD_CarControl_NoTimeLimit,             /*Car Movement Direction Control Without Time Limit*/
  CMD_MotorControl_Speed,                 /*Motor Speed Control*/
  CMD_ServoControl,                       /*Servo Motor Control*/
  CMD_LightingControl_TimeLimit,          /*RGB Lighting Control With Time Limit*/
  CMD_LightingControl_NoTimeLimit,        /*RGB Lighting Control Without Time Limit*/

};


