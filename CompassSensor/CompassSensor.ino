#include <Wire.h>
int compassAddress = 0x01; //we got this from I2C Scanner
int TestValue;  //variable where we will store compass heading

void setup() {
  Serial.begin(9600); //sets up Serial monitor
  //The code below turns on i2c, opens communication to compass
  //sensor, and does a test connection.
  Wire.begin();  //turn on i2c
  Wire.beginTransmission(compassAddress); //open communication to sensor 
  Wire.write(0x00); //blank packet
  Wire.endTransmission(); //close communication
  while(Wire.available() > 0)
     Wire.read();
}

void loop() {   
  ReadCompassSensor();  //calls the function listed below
  Serial.println(TestValue); //prints the compass heading
  delay(100); //delay for reading output
}

void ReadCompassSensor(){
  //this code lets the arduino know you want to talk to the compass Sensor
  Wire.beginTransmission(compassAddress);
  Wire.write(0x44);
  Wire.endTransmission();

  //the code below requests 2 bytes of information and then combines them
  //to make a number 0-360 that it saves in the variable TestValue
  Wire.requestFrom(compassAddress, 2); 
  while(Wire.available() < 2);
  byte lowbyte = Wire.read();  
  byte highbyte = Wire.read();
  TestValue = word(highbyte, lowbyte); 
}
