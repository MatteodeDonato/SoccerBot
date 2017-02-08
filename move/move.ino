#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <HTInfraredSeeker.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Math.h>
#include <Wire.h>
int compassAddress = 0x01; //we got this from I2C Scanner
int TestValue;  //variable where we will store compass heading
int FWD;
const int buttonPin = 2;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status
// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers


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
//ultrasonic
// Pins
const int TRIG_PIN = 4;
const int ECHO_PIN = 5;

// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;

/*
  Send register address and the byte value you want to write the magnetometer and
  loads the destination register with the value you send
*/
void Writei2cRegisters(byte numberbytes, byte command)
{
  byte i = 0;

  Wire.beginTransmission(SensorAddressWrite);   // Send address with Write bit set
  Wire.write(command);                          // Send command, normally the register address
  for (i = 0; i < numberbytes; i++)
    // Send data
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

  Serial.println("TCS34725 not responding");
}


Adafruit_MotorShield motorShield = Adafruit_MotorShield();

Adafruit_DCMotor *frontLeft = motorShield.getMotor(1);
Adafruit_DCMotor *backLeft = motorShield.getMotor(2);
Adafruit_DCMotor *frontRight = motorShield.getMotor(3);
Adafruit_DCMotor *backRight = motorShield.getMotor(4);
int speed1 = 50;
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
  Serial.println("Dir\tStrength"); //Prints Dir & Strength at top
  InfraredSeeker::Initialize(); //initializes the IR sensor

  Serial.begin(9600); //sets up Serial monitor
  //The code below turns on i2c, opens communication to compass
  //sensor, and does a test connection.
  Wire.begin();  //turn on i2c
  Wire.beginTransmission(compassAddress); //open communication to sensor
  Wire.write(0x00); //blank packet
  Wire.endTransmission(); //close communication
  while (Wire.available() > 0)
    Wire.read();


  ReadCompassSensor();
  FWD = TestValue;

  pinMode(buttonPin, INPUT);

  //ULTRASONIC

  // The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);

  // We'll use the serial monitor to view the sensor output
  Serial.begin(9600);

}


void ReadCompassSensor() {
  //this code lets the arduino know you want to talk to the compass Sensor
  Wire.beginTransmission(compassAddress);
  Wire.write(0x44);
  Wire.endTransmission();

  //the code below requests 2 bytes of information and then combines them
  //to make a number 0-360 that it saves in the variable TestValue
  Wire.requestFrom(compassAddress, 2);
  while (Wire.available() < 2);
  byte lowbyte = Wire.read();
  byte highbyte = Wire.read();
  TestValue = word(highbyte, lowbyte);
}
//loop runs repeatedly
void loop() {

  ReadCompassSensor();  //calls the function listed below
  Serial.print("compass:\t"); //prints the compass heading
  Serial.println(TestValue);
  //delay(1); //delay for reading output

  //delay (1);
  //IR
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();

  Serial.print(InfraredBall.Direction); //Print the Direction Number
  Serial.print("\t"); // Print a tab
  Serial.print(InfraredBall.Strength); //Print the Strength Number
  Serial.println(); //Print a new line

  //delay(100); //delay a tenth of a second

  //IR

  Readi2cRegisters(8, ColorAddress);
  clear_color = (unsigned int)(i2cReadBuffer[1] << 8) + (unsigned int)i2cReadBuffer[0];
  red_color = (unsigned int)(i2cReadBuffer[3] << 8) + (unsigned int)i2cReadBuffer[2];
  green_color = (unsigned int)(i2cReadBuffer[5] << 8) + (unsigned int)i2cReadBuffer[4];
  blue_color = (unsigned int)(i2cReadBuffer[7] << 8) + (unsigned int)i2cReadBuffer[6];

  //Serial.println(clear_color);
  // Serial.println(red_color);
  Serial.println(green_color);
  // Serial.println(blue_color);
  // stay on green

  if ((green_color > 170) && (green_color < 300)) {
    Serial.println("detecting green");
    delay(500);
  } else {
    Serial.println("detecting not green");
    frontLeft->run(BACKWARD);
    backLeft->run(BACKWARD);
    frontRight->run(BACKWARD);
    backRight->run(BACKWARD);
    delay(500);
    frontLeft->run(FORWARD);
    backLeft->run(FORWARD);
    frontRight->run(BACKWARD);
    backRight->run(BACKWARD);
    delay(200);
  }




  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);

  
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState ==  LOW ) {
   



    if ((InfraredBall.Direction > 3) && (InfraredBall.Direction < 7)) {
      Serial.println("ball dead ahead");
      frontLeft->run(BACKWARD);
      backLeft->run(BACKWARD);
      frontRight->run(FORWARD);
      backRight->run(FORWARD);

    } else if ((InfraredBall.Direction > 0) && (InfraredBall.Direction < 4)) {
      Serial.println("ball to the left");
      frontLeft->run(FORWARD);
      backLeft->run(FORWARD);
      frontRight->run(FORWARD);
      backRight->run(FORWARD);

    }
    else if ((InfraredBall.Direction > 6) && (InfraredBall.Direction < 8)) {
      Serial.println("ball to the right");
      frontLeft->run(BACKWARD);
      backLeft->run(BACKWARD);
      frontRight->run(BACKWARD);
      backRight->run(BACKWARD);

    }
  }





  //GO TO GOAL

  //botton press here
  else {







    // if the input just went from LOW and HIGH and we've waited long enough
    // to ignore any noise on the circuit, toggle the output pin and remember
    // the tim


    //UTRASONIC

    unsigned long t1;
    unsigned long t2;
    unsigned long pulse_width;
    float cm;
    float inches;

    // Hold the trigger pin high for at least 10 us
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Wait for pulse on echo pin
    while ( digitalRead(ECHO_PIN) == 0 );

    // Measure how long the echo pin was held high (pulse width)
    // Note: the micros() counter will overflow after ~70 min
    t1 = micros();
    while ( digitalRead(ECHO_PIN) == 1);
    t2 = micros();
    pulse_width = t2 - t1;

    // Calculate distance in centimeters and inches. The constants
    // are found in the datasheet, and calculated from the assumed speed
    //of sound in air at sea level (~340 m/s).
    cm = pulse_width / 58.0;
    inches = pulse_width / 148.0;

    // Print out results
    if ( pulse_width > MAX_DIST ) {
      Serial.println("Out of range");
    } else {
      Serial.println(cm);
      Serial.print(" cm \t");
      Serial.println(inches);
      Serial.print(" in");
    }


    //spin roller backwards until ultrasonic sees goal within certian distance then reverse roller to lauch ball.
    if (cm <= 20) {
      digitalWrite(3, HIGH);
      digitalWrite(2, LOW);
    }
    else {
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
    }



    if ((TestValue > FWD - 10) && (TestValue < (FWD + 10) % 360)) {
      Serial.println("GOAL dead ahead");
      frontLeft->run(BACKWARD);
      backLeft->run(BACKWARD);
      frontRight->run(FORWARD);
      backRight->run(FORWARD);

    } else if ((TestValue < FWD - 10) && (TestValue > (FWD - 180) % 360)) {
      Serial.println("GOAL to the left");
      frontLeft->run(FORWARD);
      backLeft->run(FORWARD);
      frontRight->run(FORWARD);
      backRight->run(FORWARD);

    }
    else if ((TestValue > FWD + 10) && (TestValue > (FWD +  180) % 360)) {
      Serial.println("GOAL to the right");
      frontLeft->run(BACKWARD);
      backLeft->run(BACKWARD);
      frontRight->run(BACKWARD);
      backRight->run(BACKWARD);

    }
    else
      Serial.println("GOAL???");
  }

}





