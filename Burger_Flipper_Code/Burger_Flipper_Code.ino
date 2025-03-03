#include <Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2 //uses pin 2 for onewire communication

OneWire oneWire(ONE_WIRE_BUS); //sets up onewire communcation
DallasTemperature sensor(&oneWire); //sets up the DallasTemperature library to work with the OneWire bus

Servo SpatulaServo; //Spatula Servo object
Servo ProbeServo; //Probe Servo object

int laserReceivers[] {3,4,5}; //Pins 3, 4, and 5 are used for receivers




void setup() {
  // put your setup code here, to run once:
  sensor.begin(); //initializes the sensor for arduino communication
  SpatulaServo.attach(6); //attach spatula servo to pin 9
  ProbeServo.attach(7); //attach probe servo to pin 10

  for(int i=0; i< 3; i++){
    pinMode(laserReceivers[i], INPUT); //sets each receiver pin as an input
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}






// GENERAL HELPER FUNCTIONS

float getTemperature(){
  sensor.requestTemperatures(); //requests a temperature reading from the sensor
  float temperature = sensor.getTempFByIndex(0); //stores the temperature from the sensor
  return temperature; //returns the temperature value in degrees Fahrenheit
}


void ServoSpinner(int angle1, int angle2, Servo &servo){
  servo.write(angle1); //moves the servo angle1 degrees
  delay(1000); //1 second delay
  servo.write(angle2); //moves the servo angle2 degrees  
  delay(1000); //1 second delay
}











