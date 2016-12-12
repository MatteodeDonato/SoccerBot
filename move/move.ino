#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <HTInfraredSeeker.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Math.h>

byte i2cWriteBuffer[10];
byte i2cReadBuffer[10];

#define SensorAddressWrite 0x29 //
#define SensorAddressRead 0x29 // 
#define EnableAddress 0xa0 // register address + command bits
#define ATimeAddress 0xa1 // register address + command bits
#define WTimeAddress 0xa3 // register address + command bits
#define ConfigAddress 0xad // register address + command bits
#define ControlAddress 0xaf // register address + command bits
#define IDAddress 0xb2 // register address + command bits
#define ColorAddress 0xb4 // register address + command bits

unsigned int clear_color = 0;
unsigned int red_color = 0;
unsigned int green_color = 0;
unsigned int blue_color = 0;

/*
  Send register address and the byte value you want to write the magnetometer and
  loads the destination register with the value you send
*/
void Writei2cRegisters(byte numberbytes, byte command)
{
  byte i = 0;

  Wire.beginTransmission(SensorAddressWrite);   // Send address with Write bit set
  Wire.write(command);                          // Send command, normally the register address
  for (i = 0; i < numberbytes; i++)                 // Send data
    Wire.write(i2cWriteBuffer[i]);
  Wire.endTransmission();

  delayMicroseconds(100);      // allow some time for bus to settle
}

/*
  Send register address to this function and it returns byte value
  for the magnetometer register's contents
*/
byte Readi2cRegisters(int numberbytes, byte command)
{
  byte i = 0;

  Wire.beginTransmission(SensorAddressWrite);   // Write address of read to sensor
  Wire.write(command);
  Wire.endTransmission();

  delayMicroseconds(100);      // allow some time for bus to settle

  Wire.requestFrom(SensorAddressRead, numberbytes);  // read data
  for (i = 0; i < numberbytes; i++)
    i2cReadBuffer[i] = Wire.read();
  Wire.endTransmission();

  delayMicroseconds(100);      // allow some time for bus to settle
}

void init_TCS34725(void)
{
  i2cWriteBuffer[0] = 0x10;
  Writei2cRegisters(1, ATimeAddress);   // RGBC timing is 256 - contents x 2.4mS =
  i2cWriteBuffer[0] = 0x00;
  Writei2cRegisters(1, ConfigAddress);  // Can be used to change the wait time
  i2cWriteBuffer[0] = 0x00;
  Writei2cRegisters(1, ControlAddress); // RGBC gain control
  i2cWriteBuffer[0] = 0x03;
  Writei2cRegisters(1, EnableAddress);   // enable ADs and oscillator for sensor
}

void get_TCS34725ID(void)
{
  Readi2cRegisters(1, IDAddress);
  if (i2cReadBuffer[0] = 0x44)
    Serial.println("TCS34725 is present");
  else
    Serial.println("TCS34725 not responding");
}


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

  Wire.begin();
  Serial.begin(9600);  // start serial for output
  init_TCS34725();
  get_TCS34725ID();     // get the device ID, this is just a test to see if we're connected
  
}



//loop runs repeatedly
void loop() {

  delay (10);

  Readi2cRegisters(8, ColorAddress);
  clear_color = (unsigned int)(i2cReadBuffer[1] << 8) + (unsigned int)i2cReadBuffer[0];
  red_color = (unsigned int)(i2cReadBuffer[3] << 8) + (unsigned int)i2cReadBuffer[2];
  green_color = (unsigned int)(i2cReadBuffer[5] << 8) + (unsigned int)i2cReadBuffer[4];
  blue_color = (unsigned int)(i2cReadBuffer[7] << 8) + (unsigned int)i2cReadBuffer[6];

  //Serial.println(clear_color);
 // Serial.println(red_color);
  Serial.println(green_color);
 // Serial.println(blue_color);
  
   if ((green_color > 150)&& (green_color < 400)) {
   //Serial.println("detecting green");
    frontLeft->run(FORWARD);
    backLeft->run(FORWARD);
    frontRight->run(FORWARD);
    backRight->run(FORWARD);
  }else {
   //Serial.println("detecting green");
    frontLeft->run(BACKWARD);
    backLeft->run(BACKWARD);
    frontRight->run(BACKWARD);
    backRight->run(BACKWARD);
    delay(3000);
    frontLeft->run(FORWARD);
    backLeft->run(FORWARD);
    frontRight->run(BACKWARD);
    backRight->run(BACKWARD);
    delay(500);
  }
}

// working version
//if((red_color>blue_color) && (red_color>green_color)){
//Serial.println("detecting red");
//frontLeft->run(FORWARD);
//backLeft->run(FORWARD);
//frontRight->run(BACKWARD);
// backRight->run(FORWARD);
// }
//  else if((green_color>blue_color) && (green_color>red_color)){
//    Serial.println("detecting green")
//    frontLeftDirection = FORWARD;
//    backLeftDirection = FORWARD;
//    frontRightDirection = FORWARD;
//    backRightDirection = FORWARD;
//}
//  else if((blue_color>red_color) && (blue_color>green_color)){
//    Serial.println("detecting blue");
//    frontLeftDirection = FORWARD;
//    backLeftDirection = FORWARD;
//    frontRightDirection = BACKWARD;
//    backRightDirection = BACKWARD;
//  }
//  else
//    Serial.println("color not detectable");
//    }





