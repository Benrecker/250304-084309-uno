#include "GENG1201_Project.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include "MPU6050_getdata.h"
#include <stdio.h>
#include <math.h>
#include <Servo.h>
#include "ApplicationFunctionSet_xxx0.h"

enum State {
    FORWARD,
    TURN_LEFT,
    TURN_RIGHT,
    REVERSE
};

enum SixPos {
    L1,
    L2,
    L3,
    R1,
    R2,
    R3
};
DeviceDriverSet_Servo servoClass;

bool hasMoved = false;

int servoPinFert = 11;
float yaw, initialYaw;

int distanceFront, distanceLeft, distanceRight;

State currentState;
SixPos currentPos;

Servo servo_11;

int ReadRemote();

float yaw_angle = 0;

void setup(){

    servo_11.attach(11, 0, 180);
    MPU6050Getdata.MPU6050_calibration();  
    Init();
    int readremote = 0;
    servoControl(90);
    servoClass.DeviceDriverSet_Servo_controls(PIN_Servo_y,0);
    MPU6050Getdata.agz = 0;

}

void loop(){
    void printcoloursvalues();
    int readremote = ReadRemote();

    if(readremote == 1){
      printcoloursvalues();

    if (function_xxx(TrackingData_M, 0 , 100)) move(Forward, 150);

    else if (function_xxx(TrackingData_L, 0 , 100)) move(Left, 45);

    else if (function_xxx(TrackingData_R, 0 , 100)) move(Right, 45);

    else move(stop_it, 0);

    } else if(readremote == 2){

    readUltrasonicSensor (get_Distance);

    distanceFront = get_Distance;

    Serial.println("Front: " + String(distanceFront));

    if (distanceFront < 20) {
        move(stop_it,0);
        servoControl(180);  // Check left
        delay(500);
        readUltrasonicSensor (get_Distance);
         distanceLeft = get_Distance;

        servoControl(0);
         // Check right
        delay(500);
        readUltrasonicSensor (get_Distance);
        int distanceRight = get_Distance;

        servoControl(90); // Reset to front

        if (distanceLeft > distanceRight) {
            currentState = TURN_LEFT;
        } else if (distanceRight > distanceLeft) {
            currentState = TURN_RIGHT;
        } else {
            currentState = FORWARD;
        }
    }

    // Switch case for movement decision
    switch (currentState) {
        case FORWARD:
           move(Forward,255);
            break;

        case TURN_LEFT:
            move(Left,100);
            delay(500);
            break;

        case TURN_RIGHT:
            move(Right,100);
            delay(500);
            break;

        case REVERSE:
            move(Backward,100);
            delay(700);
            break;
    }
    currentState = FORWARD;

    }else if(readremote == 3){

    if(!hasMoved){
      for(int angle = 0; angle <180; angle += 20){
        servo_11.write(angle);
        delay(500);
      }
    }
    hasMoved = true;
    if(!hasMoved){
        for(int angle = 0; angle <180; angle += 20){
          servo_11.write(angle);
          delay(500);
        }
      }
      hasMoved = true;
  }
}
void printcoloursvalues(){

    Serial.print("R = ");
    Serial.println(TrackingData_R);
    Serial.print("M = ");
    Serial.println(TrackingData_M);
    Serial.print("L = ");
    Serial.println(TrackingData_L);

}

  



