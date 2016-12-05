#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <HTInfraredSeeker.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield motorShield = Adafruit_MotorShield(); 

Adafruit_DCMotor *frontLeft = motorShield.getMotor(1);
Adafruit_DCMotor *backLeft = motorShield.getMotor(2);
Adafruit_DCMotor *frontRight = motorShield.getMotor(3);
Adafruit_DCMotor *backRight = motorShield.getMotor(4);
int speed1 = 120;
void setup() {
   motorShield.begin();
  frontLeft->setSpeed(speed1); 
  backLeft->setSpeed(speed1);
  frontRight->setSpeed(speed1); 
  backRight->setSpeed(speed1); 
}

//loop runs repeatedly
void loop() {   
 //forward movement
    frontLeft->run(FORWARD); 
    backLeft->run(FORWARD);
    frontRight->run(FORWARD);
    backRight->run(FORWARD);
  //sideways
  //frontLeft->run(BACKWARD); 
  //backLeft->run(FORWARD);
  //frontRight->run(FORWARD);
  //backRight->run(BACKWARD);
  
  
}


