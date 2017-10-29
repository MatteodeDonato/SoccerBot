#include <Servo.h>

byte servoPin4 = 5;
byte servoPin1 = 2;
byte servoPin2 = 3;
byte servoPin3 = 4;
Servo servo;

void setup() {
}

void loop() {
servo.attach(servoPin1);
Serial.begin(9600);
servo.writeMicroseconds(1500); // send "stop" signal to ESC.
delay(5000); // delay to allow the ESC to recognize the stopped signal
int signal1 = 1600; // Set signal value, which should be between 1100 and 1900
servo.writeMicroseconds(signal1); // Send signal to ESC.
delay(5000);
Serial.println("M1");

servo.attach(servoPin2);
Serial.begin(9600);
servo.writeMicroseconds(1500); // send "stop" signal to ESC.
delay(5000); // delay to allow the ESC to recognize the stopped signal
int signal2 = 1600; // Set signal value, which should be between 1100 and 1900
servo.writeMicroseconds(signal2); // Send signal to ESC.
delay(5000);
Serial.println("M2");

servo.attach(servoPin3);
Serial.begin(9600);
servo.writeMicroseconds(1500); // send "stop" signal to ESC.
delay(5000); // delay to allow the ESC to recognize the stopped signal
int signal3 = 1600; // Set signal value, which should be between 1100 and 1900
servo.writeMicroseconds(signal3); // Send signal to ESC.
delay(5000);
Serial.println("M3");

servo.attach(servoPin4);
Serial.begin(9600);
servo.writeMicroseconds(1500); // send "stop" signal to ESC.
delay(5000); // delay to allow the ESC to recognize the stopped signal
int signal4 = 1600; // Set signal value, which should be between 1100 and 1900
servo.writeMicroseconds(signal4); // Send signal to ESC.
delay(5000);
Serial.println("M4");
}

void North(){}
void South(){}
void East(){}
void West(){}
void NorthEast(){}
void NorthWest(){}
void SouthEast(){}
void SouthWest(){}
