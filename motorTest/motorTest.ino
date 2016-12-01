#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield Samira = Adafruit_MotorShield(); 

Adafruit_DCMotor *frontMotor = Samira.getMotor(1);
Adafruit_DCMotor *rightMotor = Samira.getMotor(2);
Adafruit_DCMotor *leftMotor = Samira.getMotor(3);
Adafruit_DCMotor *Motor = Samira.getMotor(4);


void setup(){

  Samira.begin();

}


void loop(){

  frontMotor->setSpeed(255); 
  frontMotor->run(FORWARD);

  
}

