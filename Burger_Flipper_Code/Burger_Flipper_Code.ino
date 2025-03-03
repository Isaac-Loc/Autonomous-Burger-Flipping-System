#include <Servo.h>

Servo SpatulaServo;
Servo ProbeServo;

void setup() {
  // put your setup code here, to run once:
  SpatulaServo.attach(9); //attach spatula servo to pin 9
  ProbeServo.attach(10); //attach probe servo to pin 10
}

void ServoSpinner(int angle1, int angle2, Servo servo){
  servo.write(angle1); //moves the servo angle1 degrees
  delay(1000); //1 second delay
  servo.write(angle2); //moves the servo angle2 degrees  
  delay(1000); //1 second delay
}



void loop() {
  // put your main code here, to run repeatedly:

}
