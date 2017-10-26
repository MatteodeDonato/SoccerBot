#include <Servo.h>

byte servoPin4 = 5;
byte servoPin1 = 2;
byte servoPin2 = 3;
byte servoPin3 = 4;
Servo servo;

void setup() {
    servo.attach(servoPin4);
Serial.begin(9600);
servo.writeMicroseconds(1500); // send "stop" signal to ESC.
  delay(5000); // delay to allow the ESC to recognize the stopped signal
}

void loop() {
  int signal = 1900; // Set signal value, which should be between 1100 and 1900
  servo.writeMicroseconds(signal); // Send signal to ESC.
  delay(5000);
Serial.print("HI");
}

void North(){}
void South(){}
void East(){}
void West(){}
void NorthEast(){}
void NorthWest(){}
void SouthEast(){}
void SouthWest(){}
