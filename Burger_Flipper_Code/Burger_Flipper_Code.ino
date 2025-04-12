#include <Servo.h>

Servo SpatulaServo;

#define IN1_2 2
#define IN1_1 3
#define ENA1 4

#define laser1 5
#define receiver1 6

void setup() {
  // put your setup code here, to run once:
  SpatulaServo.attach(7);
  
  pinMode(ENA1, OUTPUT);
  pinMode(IN1_1, OUTPUT);
  pinMode(IN1_2, OUTPUT);

  pinMode(laser1, OUTPUT);
  pinMode(receiver1, INPUT);
  digitalWrite(laser1, HIGH);

  Serial.begin(9600);
}

void loop() {
  int value1 = digitalRead(receiver1);
  moveForward(ENA1, IN1_1, IN1_2, 250, 3000);
  /*SpatulaServo.write(0);
  delay(5000);
  SpatulaServo.write(180);
  delay(5000);*/

  //Serial.print(value1);
  /*if(value1 == 1){
    moveForward(ENA1, IN1_1, IN1_2, 250, 3000);
    delay(4000);
    SpatulaServo.write(180);
    delay(2000);
    moveBackward(ENA1, IN1_1, IN1_2, 250, 3000);
    delay(4000);
    SpatulaServo.write(0);
    delay(2000);
  }*/
}



void moveForward(int enaPin, int in1Pin, int in2Pin, int speed, int duration) {
  analogWrite(enaPin, speed);   // Set motor speed (0-255)
  digitalWrite(in1Pin, HIGH);    // Motor moves forward
  digitalWrite(in2Pin, LOW);
  delay(duration);               // Run motor for specified time (milliseconds)
  stopMotor(in1Pin, in2Pin);     // Stop motor after moving
}

void moveBackward(int enaPin, int in1Pin, int in2Pin, int speed, int duration) {
  analogWrite(enaPin, speed);   // Set motor speed (0-255)
  digitalWrite(in1Pin, LOW);     // Motor moves backward
  digitalWrite(in2Pin, HIGH);
  delay(duration);               // Run motor for specified time (milliseconds)
  stopMotor(in1Pin, in2Pin);     // Stop motor after moving
}

void stopMotor(int in1Pin, int in2Pin) {
  digitalWrite(in1Pin, LOW);   // Stop motor (no direction)
  digitalWrite(in2Pin, LOW);   // Stop motor (no direction)
}

