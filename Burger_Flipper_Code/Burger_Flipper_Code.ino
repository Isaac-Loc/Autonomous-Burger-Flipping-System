#include <DallasTemperature.h>
#include <OneWire.h>
#include <Servo.h>

Servo SpatulaServo; //Spatula Servo object

//DC Motor 1 Pins (Pins 0, 1, 2) Probe DC y axis - 12v, 1000 rpm DC Motor 
#define ENA1 10  // PWM pin to control motor speed (0-255)
#define IN1_1 13 // Motor direction control pin 1 (Forward)
#define IN1_2 2 // Motor direction control pin 2 (Backward)

//DC Motor 2 Pins (Pins 3, 4, 5) Spatula DC - 24v, 1000 rpm DC Motor
#define ENA2 3  // PWM pin to control motor speed (0-255)
#define IN2_1 4 // Motor direction control pin 1 (Forward)
#define IN2_2 5 // Motor direction control pin 2 (Backward)

//DC Motor 3 Pins (Pins 6, 7, 8) Probe DC x axis - 24v, 800 rpm DC Motor
#define ENA3 6  // PWM pin to control motor speed (0-255)
#define IN3_1 7 // Motor direction control pin 1 (Forward)
#define IN3_2 8 // Motor direction control pin 2 (Backward)

//ALL LASERS AND RECEIVER PINS
#define laser1 17 //Pin for laser 1
#define laser2 20 //Pin for laser 2
#define laser3 19 //Pin for laser 3
//#define laser4 13 //Pin for laser 4

#define receiver1 14 //Pin for receiver 1
#define receiver2 15 //Pin for receiver 2
#define receiver3 16 //Pin for receiver 3
//#define receiver4 17 //Pin for receiver 4

#define ONE_WIRE_BUS 18
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float Celsius =0.0;
float Fahrenheit = 0.0;


void setup() {
  // put your setup code here, to run once:
  SpatulaServo.attach(9); //attach spatula servo to pin 6

   // Initialize motor pins
  pinMode(ENA1, OUTPUT);  // Motor 1 speed control
  pinMode(IN1_1, OUTPUT); // Motor 1 direction control (Forward)
  pinMode(IN1_2, OUTPUT); // Motor 1 direction control (Backward)
  
  pinMode(ENA2, OUTPUT);  // Motor 2 speed control
  pinMode(IN2_1, OUTPUT); // Motor 2 direction control (Forward)
  pinMode(IN2_2, OUTPUT); // Motor 2 direction control (Backward)

  pinMode(ENA3, OUTPUT);  // Motor 3 speed control
  pinMode(IN3_1, OUTPUT); // Motor 3 direction control (Forward)
  pinMode(IN3_2, OUTPUT); // Motor 3 direction control (Backward)

  pinMode(laser1, OUTPUT); // set the laser pin to output mode
  pinMode(receiver1, INPUT); // set the laser pin to output mode
  digitalWrite(laser1, HIGH); // emit red laser

  pinMode(laser2, OUTPUT); // set the laser pin to output mode
  pinMode(receiver2, INPUT); // set the laser pin to output mode
  digitalWrite(laser2, HIGH);// emit red laser

  pinMode(laser3, OUTPUT); // set the laser pin to output mode
  pinMode(receiver3, INPUT); // set the laser pin to output mode
  digitalWrite(laser3, HIGH);// emit red laser

  /*pinMode(laser4, OUTPUT); // set the laser pin to output mode
  pinMode(receiver4, INPUT); // set the laser pin to output mode
  digitalWrite(laser4, HIGH); // emit red laser*/

  Serial.begin(9600);
  sensors.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //1 is not connected 0 is connected to receiver
  moveForward(ENA1,IN1_1,IN1_2,255,5000);
  int value1 = digitalRead(receiver1); // receiver/detector send either LOW or HIGH (no analog values!)
  int value2 = digitalRead(receiver2); // receiver/detector send either LOW or HIGH (no analog values!)
  int value3 = digitalRead(receiver3); // receiver/detector send either LOW or HIGH (no analog values!)
  //int value4 = digitalRead(receiver4); // receiver/detector send either LOW or HIGH (no analog values!)

  //Serial.print(value1);
  //Serial.print(value2);
  //Serial.print(value3);
  //Serial.print(value4);

  /*if(value1==1){
    moveForward(ENA2, IN2_1, IN2_2, 255, 5000); //Move spatula DC Motor to pick up the patty
    delay(3000);
    moveBackward(ENA2, IN2_1, IN2_2, 255, 5000); //Move spatula DC Motor back to middle of the grill
  */
    /*SpatulaServo.write(180); //Flip spatula to place patty in the center
    delay(3000); //1 second delay
    SpatulaServo.write(0); //Flip spatula back to default position
    
    moveBackward(ENA2, IN2_1, IN2_2, 255, 8000); //Move spatula DC Motor back to the start
    delay(5000); //5 second delay
    moveForward(ENA3, IN3_1, IN3_2, 255, 8000); //Move probe x-DC Motor to the middle of the grill
    moveForward(ENA1,IN1_1,IN1_2,255,5000); //Move probe y-DC Motor 1/3 of the way to the grill
  */
  //}
}


// GENERAL HELPER FUNCTIONS

//Temperature probe
/*float GetTemperature(){
  sensors.requestTemperatures();
    Celsius = sensors.getTempCByIndex(0);
    Fahrenheit = sensors.toFahrenheit(Celsius);
    return Fahrenheit;
}*/

//SERVO MOTORS FUNCTIONALITY


void ServoSpinner(int angle1, int angle2, Servo &servo){
  servo.write(angle1); //moves the servo angle1 degrees
  delay(1000); //1 second delay
  servo.write(angle2); //moves the servo angle2 degrees  
  delay(1000); //1 second delay
}



//DC MOTOR FUNCTIONALITY


// Function to move the motor forward

void moveForward(int enaPin, int in1Pin, int in2Pin, int speed, int duration) {
  analogWrite(enaPin, speed);   // Set motor speed (0-255)
  digitalWrite(in1Pin, HIGH);    // Motor moves forward
  digitalWrite(in2Pin, LOW);
  delay(duration);               // Run motor for specified time (milliseconds)
  stopMotor(in1Pin, in2Pin);     // Stop motor after moving
}

//How to Call the above function: 
/* Move motor 1 forward with speed 200 for 5 seconds

  moveForward(ENA1, IN1_1, IN2_1, 200, 5000); */



// Function to move the motor backward

void moveBackward(int enaPin, int in1Pin, int in2Pin, int speed, int duration) {
  analogWrite(enaPin, speed);   // Set motor speed (0-255)
  digitalWrite(in1Pin, LOW);     // Motor moves backward
  digitalWrite(in2Pin, HIGH);
  delay(duration);               // Run motor for specified time (milliseconds)
  stopMotor(in1Pin, in2Pin);     // Stop motor after moving
}

//How to Call the Above function:
/*Move motor 1 backward with speed 200 for 5 seconds

  moveBackward(ENA1, IN1_1, IN2_1, 200, 5000); */


// Function to stop the motor

void stopMotor(int in1Pin, int in2Pin) {
  digitalWrite(in1Pin, LOW);   // Stop motor (no direction)
  digitalWrite(in2Pin, LOW);   // Stop motor (no direction)
}

//How to call the Above function:
/*Stop motor after moving

  StopMotor(in1Pin, in2Pin); */    







