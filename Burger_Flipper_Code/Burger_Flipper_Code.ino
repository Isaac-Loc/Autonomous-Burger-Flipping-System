#include <Servo.h>

Servo SpatulaServo; //Spatula Servo object
Servo ProbeServo; //Probe Servo object

//int laserReceivers[] {3,4,5}; //Pins 3, 4, and 5 are used for receivers
//int laserPin 7;

//DC Motor 1 Pins (Pins 0, 1, 2)
#define ENA1 0  // PWM pin to control motor speed (0-255)
#define IN1_1 1 // Motor direction control pin 1 (Forward)
#define IN2_1 2 // Motor direction control pin 2 (Backward)

//DC Motor 2 Pins (Pins 3, 4, 5)
#define ENA2 3  // PWM pin to control motor speed (0-255)
#define IN1_2 4 // Motor direction control pin 1 (Forward)
#define IN2_2 5 // Motor direction control pin 2 (Backward)

//DC Motor 3 Pins (Pins 6, 7, 8)
#define ENA3 6  // PWM pin to control motor speed (0-255)
#define IN1_3 7 // Motor direction control pin 1 (Forward)
#define IN2_3 8 // Motor direction control pin 2 (Backward)




void setup() {
  // put your setup code here, to run once:
  SpatulaServo.attach(6); //attach spatula servo to pin 6

  /*for(int i=0; i< 3; i++){
    pinMode(laserReceivers[i], INPUT); //sets each receiver pin as an input
  }*/

  pinMode(3,INPUT); 
  //pinMode(laserPin,OUTPUT);
  //digitalWrite(laserPin,HIGH);

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
  //int value = digitalRead(pinReceiver);
  //Serial.println(value);

  moveForward(ENA1,IN1_1,IN2_1,255,10);
  moveForward(ENA2,IN1_2,IN2_2,255,10);
  moveForward(ENA3,IN1_3,IN2_3,255,10);
}






// GENERAL HELPER FUNCTIONS


//LASER RECEIVER CHECKER FUNCTIONALITY
/*
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
*/

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

int pinA = 11;int pinB = 7;int pinC = 4;int pinD = 2;
int pinE = 1;int pinF = 10;int pinG = 5;
int pinDP = 3;int D1 = 12;int D2 = 9;int D3 = 8; int D4 = 6;

void setup() {//set all segments & digits as outputs
pinMode(pinA, OUTPUT);
pinMode(pinB, OUTPUT);
pinMode(pinC, OUTPUT);
pinMode(pinD, OUTPUT);
pinMode(pinE, OUTPUT);
pinMode(pinF, OUTPUT);
pinMode(pinG, OUTPUT);
pinMode(pinDP, OUTPUT);
pinMode(D1, OUTPUT);
pinMode(D2, OUTPUT);
pinMode(D3, OUTPUT);
pinMode(D4, OUTPUT);
}

void loop() {
  
  digit1();zero();delay(500);
  digit2();one();delay(500);
  digit3();two();delay(500);
  digit4();three();delay(500);
  digit3();four();delay(500);
  digit2();five();delay(500);
  digit1();six();delay(500);
  digit2();seven();delay(500);
  digit3();eight();delay(500);
  digit4();nine();delay(500);
 
  all4Digits();
  allNumbers();

}


//functions representing numbers 0-9
void zero(){
digitalWrite(pinA, LOW);
digitalWrite(pinB, LOW);
digitalWrite(pinC, LOW);
digitalWrite(pinD, LOW);
digitalWrite(pinE, LOW);
digitalWrite(pinF, LOW);
digitalWrite(pinG, HIGH);
  }

  void one(){
digitalWrite(pinA, HIGH);
digitalWrite(pinB, LOW);
digitalWrite(pinC, LOW);
digitalWrite(pinD, HIGH);
digitalWrite(pinE, HIGH);
digitalWrite(pinF, HIGH);
digitalWrite(pinG, HIGH);
}

void two(){
  digitalWrite(pinA, LOW);
digitalWrite(pinB, LOW);
digitalWrite(pinC, HIGH);
digitalWrite(pinD, LOW);
digitalWrite(pinE, LOW);
digitalWrite(pinF, HIGH);
digitalWrite(pinG, LOW);
  }
  
  void three(){
    digitalWrite(pinA, LOW);
digitalWrite(pinB, LOW);
digitalWrite(pinC, LOW);
digitalWrite(pinD, LOW);
digitalWrite(pinE, HIGH);
digitalWrite(pinF, HIGH);
digitalWrite(pinG, LOW);
    }
    
  void four(){
    digitalWrite(pinA, HIGH);
digitalWrite(pinB, LOW);
digitalWrite(pinC, LOW);
digitalWrite(pinD, HIGH);
digitalWrite(pinE, HIGH);
digitalWrite(pinF, LOW);
digitalWrite(pinG, LOW);
    }
    
  void five(){
    digitalWrite(pinA, LOW);
digitalWrite(pinB, HIGH);
digitalWrite(pinC, LOW);
digitalWrite(pinD, LOW);
digitalWrite(pinE, HIGH);
digitalWrite(pinF, LOW);
digitalWrite(pinG, LOW);
    }
    
  void six(){
    digitalWrite(pinA, LOW);
digitalWrite(pinB, HIGH);
digitalWrite(pinC, LOW);
digitalWrite(pinD, LOW);
digitalWrite(pinE, LOW);
digitalWrite(pinF, LOW);
digitalWrite(pinG, LOW);
    }
    
  void seven(){
    digitalWrite(pinA, LOW);
digitalWrite(pinB, LOW);
digitalWrite(pinC, LOW);
digitalWrite(pinD, HIGH);
digitalWrite(pinE, HIGH);
digitalWrite(pinF, HIGH);
digitalWrite(pinG, HIGH);
    }
    
  void eight(){
    digitalWrite(pinA, LOW);
digitalWrite(pinB, LOW);
digitalWrite(pinC, LOW);
digitalWrite(pinD, LOW);
digitalWrite(pinE, LOW);
digitalWrite(pinF, LOW);
digitalWrite(pinG, LOW);
    }
    
  void nine(){
    digitalWrite(pinA, LOW);
digitalWrite(pinB, LOW);
digitalWrite(pinC, LOW);
digitalWrite(pinD, HIGH);
digitalWrite(pinE, HIGH);
digitalWrite(pinF, LOW);
digitalWrite(pinG, LOW);
    }

    void allNumbers(){
one();delay(500);
two();delay(500);
three();delay(500);
four();delay(500);
five();delay(500);
six();delay(500);
seven();delay(500);
eight();delay(500);
nine();delay(500);
      }

  void turnOffAllSegments(){
          digitalWrite(pinA, LOW);
digitalWrite(pinB, LOW);
digitalWrite(pinC, LOW);
digitalWrite(pinD, LOW);
digitalWrite(pinE, LOW);
digitalWrite(pinF, LOW);
digitalWrite(pinG, LOW);
          }


    //functions to select individual digits on the display
    void digit1(){
      digitalWrite(D1, HIGH);
digitalWrite(D2, LOW);
digitalWrite(D3, LOW);
digitalWrite(D4, LOW);
      }
      
    void digit2(){
      digitalWrite(D1, LOW);
digitalWrite(D2, HIGH);
digitalWrite(D3, LOW);
digitalWrite(D4, LOW);
      }
      
    void digit3(){
      digitalWrite(D1, LOW);
digitalWrite(D2, LOW);
digitalWrite(D3, HIGH);
digitalWrite(D4, LOW);
      }
      
    void digit4(){
      digitalWrite(D1, LOW);
digitalWrite(D2, LOW);
digitalWrite(D3, LOW);
digitalWrite(D4, HIGH);
      }

      void all4Digits(){
        digitalWrite(D1, HIGH);
digitalWrite(D2, HIGH);
digitalWrite(D3, HIGH);
digitalWrite(D4, HIGH);
        }
        












