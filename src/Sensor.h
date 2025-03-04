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
// infraRed
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
//const auto& move = ApplicationFunctionSet_SmartRobotCarMotionControl;



//Servo - Ultrasonic sensor position
 DeviceDriverSet_Servo AppServo1;
 void servoControl (unsigned int Position_angle){
	AppServo1.DeviceDriverSet_Servo_control(Position_angle);
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
 /*  time_t now;
  struct tm * timeinfo;
  time(&now);
  timeinfo = localtime(&now);  
  Serial.println(timeinfo->tm_hour);
*/
// Serial.print("time = ");
// Serial.println(t);

//#include <time.h>
//#include <iostream>

//using namespace std;

//int main() {
//	time_t current_time;

//	current_time = time(NULL);

//	cout << current_time/3.154e+7;
//	cout << " seconds has passed since 00:00:00 GMT, Jan 1, 1970";

//	return 0;
//}

}

static boolean
function_xxx(long x, long s, long e) //f(x)
{
  if (s <= x && x <= e)
    return true;
  else
    return false;
}
 
