#include <DallasTemperature.h>
#include <OneWire.h>
#include <Servo.h>

Servo SpatulaServo; //Spatula Servo object

//DC Motor 1 Pins (Pins 10, 13, 2) Probe DC y axis
#define ENA1 10  // PWM pin to control motor speed (0-255)
#define IN1_1 13 // Motor direction control pin 1 (Forward)
#define IN1_2 2 // Motor direction control pin 2 (Backward)

//DC Motor 2 Pins (Pins 3, 4, 5) Spatula DC
#define ENA2 3  // PWM pin to control motor speed (0-255)
#define IN2_1 4 // Motor direction control pin 1 (Forward)
#define IN2_2 5 // Motor direction control pin 2 (Backward)

//DC Motor 3 Pins (Pins 6, 7, 8) Probe DC x axis
#define ENA3 6  // PWM pin to control motor speed (0-255)
#define IN3_1 7 // Motor direction control pin 1 (Forward)
#define IN3_2 8 // Motor direction control pin 2 (Backward)

//ALL LASERS AND RECEIVER PINS
#define laser1 14 //Pin for laser 1
#define laser2 15 //Pin for laser 2
#define laser3 16 //Pin for laser 3
#define laser4 17 //Pin for laser 4

#define receiver1 18 //Pin for receiver 1
#define receiver2 19 //Pin for receiver 2
#define receiver3 20 //Pin for receiver 3
#define receiver4 21 //Pin for receiver 4

#define ONE_WIRE_BUS 22 //Pin for temperature probe
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const int KillSwitch = 23; //Pin for kill switch

// Define segment pins for 3 digit display
const int segmentPins[8] = {24, 25, 26, 27, 28, 29, 30, 31}; // A to DP
const int digitPins[3] = {32, 33, 34}; // Common cathode pins


// Define digit representation for numbers 0-9
const byte digits[10] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};


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

  pinMode(laser4, OUTPUT); // set the laser pin to output mode
  pinMode(receiver4, INPUT); // set the laser pin to output mode
  digitalWrite(laser4, HIGH); // emit red laser

  // Set segment pins as OUTPUT
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  
  // Set digit control pins as OUTPUT
  for (int i = 0; i < 3; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], HIGH); // Start with all digits off
  }

  pinMode(KillSwitch,INPUT_PULLUP); // sets up kill switch pin
  
  Serial.begin(9600);
  sensors.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  CheckKillSwitch();
  //1 is not connected 0 is connected to receiver
  int value1 = digitalRead(receiver1); // receiver/detector send either LOW or HIGH (no analog values!)
  int value2 = digitalRead(receiver2); // receiver/detector send either LOW or HIGH (no analog values!)
  int value3 = digitalRead(receiver3); // receiver/detector send either LOW or HIGH (no analog values!)
  int value4 = digitalRead(receiver4); // receiver/detector send either LOW or HIGH (no analog values!)

  if(value1==1 || value2==1 || value3==1 || value4==1){
    moveForward(ENA2, IN2_1, IN2_2, 255, 5000); //Move spatula DC Motor to pick up the patty
    delay(7000); //7 second delay
    CheckKillSwitch(); //kill switch check
    SpatulaServo.write(180); //flip the spatula 180
    moveBackward(ENA2, IN2_1, IN2_2, 255, 5000); //Move spatula DC Motor back to start of the grill
    delay(7000); //7 second delay
    CheckKillSwitch();//kill switch check
    SpatulaServo.write(0); //Flip spatula back to default position
    delay(3000); //7 second delay
    CheckKillSwitch(); //kill switch check
    moveForward(ENA3, IN3_1, IN3_2, 255, 2500); //moves probe to middle. may change to moveForward depending on probe start location
    delay(4000); //4 second delay
    CheckKillSwitch(); //kill switch check
    moveForward(ENA1, IN1_1, IN1_2, 255, 5000); //moves the probe the other axis until the end (the probe should be in the burger in theory)
    delay(8000); //7 second delay
    CheckKillSwitch(); //kill switch check
    float Temperature = 0.0;
    while(!(Temperature>=165.0)){
      Temperature = GetTemperature();
    }
    CheckKillSwitch(); //kill switch check
    moveBackward(ENA1, IN1_1, IN1_2, 255, 5000); //moves the probe backward to the middle position on the side
    delay(6000); //6 second delay
    CheckKillSwitch(); //kill switch check
    moveForward(ENA2, IN2_1, IN2_2, 255, 5000); //Move spatula DC Motor to pick up the patty
    delay(7000); //7 second delay
    CheckKillSwitch(); //kill switch check
    SpatulaServo.write(180); //flip the spatula 180
    moveBackward(ENA2, IN2_1, IN2_2, 255, 5000); //Move spatula DC Motor back to start of the grill
    delay(7000); //7 second delay
    CheckKillSwitch();//kill switch check
    SpatulaServo.write(0); //Flip spatula back to default position
    delay(3000); //7 second delay
    CheckKillSwitch(); //kill switch check
    moveForward(ENA1, IN1_1, IN1_2, 255, 5000); //moves the probe the other axis until the end (the probe should be in the burger in theory)
    delay(8000); //7 second delay
    CheckKillSwitch(); //kill switch check
    float Temperature2 = 0.0;
    while(!(Temperature2>=165.0)){
      Temperature2 = GetTemperature();
    }
    CheckKillSwitch(); //kill switch check
    moveBackward(ENA1, IN1_1, IN1_2, 255, 5000); //moves the probe backward to the middle position on the side
    delay(6000); //6 second delay
    CheckKillSwitch(); //kill switch check
    moveForward(ENA2, IN2_1, IN2_2, 255, 5000); //moves the spatula all the way to the end to pick up the patty
    delay(5000);
    CheckKillSwitch(); //kill switch check
    moveBackward(ENA2, IN2_1, IN2_2, 255,3000); //moves spatula back right before default position to prepare for plate flip
    delay(4000); //4 second delay
    ServoSpatula.write(180); //flip the spatula 180
    delay(3000); //3 second delay
    ServoSpatula.write(0); //flip spatula back to default
    moveBackward(ENA2, IN2_1, IN2_2, 255, 2000);
    delay(3000); //3 second delay
  }
}


// GENERAL HELPER FUNCTIONS

//Temperature probe
float GetTemperature(){
  sensors.requestTemperatures();
  float Celsius = sensors.getTempCByIndex(0);
  float Fahrenheit = sensors.toFahrenheit(Celsius);
  return Fahrenheit;
}

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


//Function for number shown on the 3 digit display

void displayNumber(int number) {
  int digitValues[3] = {number / 100, (number / 10) % 10, number % 10};

  for (int i = 0; i < 3; i++) {
    digitalWrite(digitPins[i], LOW); // Enable digit

    showSegments(digits[digitValues[i]]); // Show corresponding number
    
    delay(5); // Small delay for persistence of vision
    
    digitalWrite(digitPins[i], HIGH); // Disable digit
  }
}

//Helper function for display numbers

void showSegments(byte segments) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(segmentPins[i], (segments >> i) & 1);
  }
}

//Kill switch function

void CheckKillSwitch(){
  if(digitalRead(KillSwitch)==LOW){
    digitalWrite(laser1, LOW); // emit red laser
    digitalWrite(laser2, LOW); // emit red laser
    digitalWrite(laser3, LOW); // emit red laser
    digitalWrite(laser4, LOW); // emit red laser
    stopMotor(IN1_1,IN1_2);
    stopMotor(IN2_1,IN2_2);
    stopMotor(IN3_1,IN3_2);
    while(true){
      delay(30303033030303030);
    }
  }
}
