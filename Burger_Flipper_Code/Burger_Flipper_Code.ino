#include <Servo.h>

Servo SpatulaServo;
Servo ProbeServo;

void setup() {
  // put your setup code here, to run once:
  
}

void ServoSpinner(int angle, int angle2, Servo servo){
  servo.write(angle1);
  delay(1000);
  servo.write(angle2);  
  delay(1000);
}



void loop() {
  // put your main code here, to run repeatedly:

}
