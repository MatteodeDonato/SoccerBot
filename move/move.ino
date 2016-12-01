#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <HTInfraredSeeker.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield motorShield = Adafruit_MotorShield(); 

Adafruit_DCMotor *frontLeft = motorShield.getMotor(1);
Adafruit_DCMotor *backLeft = motorShield.getMotor(2);
Adafruit_DCMotor *frontRight = motorShield.getMotor(3);
Adafruit_DCMotor *backRight = motorShield.getMotor(4);

void setup() {
  motorShield.begin();
  frontLeft->setSpeed(80); 
  backLeft->setSpeed(80);
  frontRight->setSpeed(80); 
  backRight->setSpeed(80); 
}

//loop runs repeatedly
void loop() {   
 //forward movement
    frontLeft->run(FORWARD); 
    backLeft->run(FORWARD);
    frontRight->run(FORWARD);
    backRight->run(FORWARD);
 // sideways
  //frontLeft->run(BACKWARD); 
  //backLeft->run(FORWARD);
  //frontRight->run(FORWARD);
  //backRight->run(BACKWARD);
  
  
}
