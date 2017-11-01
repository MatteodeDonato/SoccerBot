#include <Servo.h>
byte servoPin4 = 5;
byte servoPin1 = 2;
byte servoPin2 = 3;
byte servoPin3 = 4;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
//ir
int ir1 = 13;
int ir1state = HIGH;      // the current state of the output pin
int ir1reading;           // the current reading from the input pin
int ir1previous = LOW;    // the previous reading from the input pi

void setup() {
  Serial.begin(9600);
  // ir
  pinMode(ir1, INPUT);
  pinMode(5, OUTPUT);
}

void loop() {
analogWrite(5, 120);
  ir1reading = digitalRead(ir1);
  if (ir1reading == HIGH ) {
      Serial.println("High");}
  else if(ir1reading == LOW){
      Serial.println("low");
  }
  delay(250);

 /* servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  servo4.attach(servoPin4);
  servo1.writeMicroseconds(1500); // send "stop" signal to ESC.
  servo2.writeMicroseconds(1500); // send "stop" signal to ESC.
  servo3.writeMicroseconds(1500); // send "stop" signal to ESC.
  servo4.writeMicroseconds(1500); // send "stop" signal to ESC.
  delay(5000); // delay to allow the ESC to recognize the stopped signal
  int signal1 = 1525; // Set signal value, which should be between 1100 and 1900
  int signal2 = 1525; // Set signal value, which should be between 1100 and 1900
  int signal3 = 1525; // Set signal value, which should be between 1100 and 1900
  int signal4 = 1525; // Set signal value, which should be between 1100 and 1900
  servo1.writeMicroseconds(signal1); // Send signal to ESC.
  Serial.println("M1");
  Serial.println(signal1);
  servo2.writeMicroseconds(signal2); // Send signal to ESC.
  Serial.println("M2");
  Serial.println(signal2);
  servo3.writeMicroseconds(signal3); // Send signal to ESC.
  Serial.println("M3");
  Serial.println(signal3);
  servo4.writeMicroseconds(signal4); // Send signal to ESC.
  Serial.println("M4");
  Serial.println(signal4);
  delay(5000);*/
}

void North() {}
void South() {}
void East() {}
void West() {}
void NorthEast() {}
void NorthWest() {}
void SouthEast() {}
void SouthWest() {}


