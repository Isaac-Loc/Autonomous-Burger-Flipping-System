#include <Servo.h>

Servo SpatulaServo; //Spatula Servo object
Servo ProbeServo; //Probe Servo object

int laserReceivers[] {3,4,5}; //Pins 3, 4, and 5 are used for receivers
int laserPin 7;

//DC Motor 1 Pins (Pins 8, 9, 10)
#define ENA1 8  // PWM pin to control motor speed (0-255)
#define IN1_1 9 // Motor direction control pin 1 (Forward)
#define IN2_1 10 // Motor direction control pin 2 (Backward)

//DC Motor 2 Pins (Pins 11, 12, 13)
#define ENA2 11 // PWM pin to control motor speed (0-255)
#define IN1_2 12 // Motor direction control pin 1 (Forward)
#define IN2_2 13 // Motor direction control pin 2 (Backward)

//DC Motor 3 Pins (Pins 14, 15, 16)
#define ENA3 14 // PWM pin to control motor speed (0-255)
#define IN1_3 15 // Motor direction control pin 1 (Forward)
#define IN2_3 16 // Motor direction control pin 2 (Backward)


void setup() {
  // put your setup code here, to run once:
  SpatulaServo.attach(6); //attach spatula servo to pin 6

  /*for(int i=0; i< 3; i++){
    pinMode(laserReceivers[i], INPUT); //sets each receiver pin as an input
  }*/

  pinMode(3,INPUT); 
  pinMode(laserPin,OUTPUT);
  digitalWrite(laserPin,HIGH);

   // Initialize motor pins
  pinMode(ENA1, OUTPUT);  // Motor 1 speed control
  pinMode(IN1_1, OUTPUT); // Motor 1 direction control (Forward)
  pinMode(IN2_1, OUTPUT); // Motor 1 direction control (Backward)
  
  pinMode(ENA2, OUTPUT);  // Motor 2 speed control
  pinMode(IN1_2, OUTPUT); // Motor 2 direction control (Forward)
  pinMode(IN2_2, OUTPUT); // Motor 2 direction control (Backward)

  pinMode(ENA3, OUTPUT);  // Motor 3 speed control
  pinMode(IN1_3, OUTPUT); // Motor 3 direction control (Forward)
  pinMode(IN2_3, OUTPUT); // Motor 3 direction control (Backward)

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int value = digitalRead(pinReceiver);
  Serial.println(value);
}






// GENERAL HELPER FUNCTIONS


//LASER RECEIVER CHECKER FUNCTIONALITY

void checkLaserReceivers() {
  for (int i = 0; i < 3; i++) {
    int laserStatus = digitalRead(laserReceivers[i]);
    if (laserStatus == LOW) { // Laser is blocked
      Serial.print("Laser Receiver ");
      Serial.print(i + 1);  // Increment index to start at 1
      Serial.println(" has lost connection!");
    }
  }
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







