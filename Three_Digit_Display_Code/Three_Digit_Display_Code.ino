#include <DallasTemperature.h>
#include <OneWire.h>


#define ONE_WIRE_BUS 10
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Define segment pins
const int segmentPins[8] = {2, 3, 4, 5, 6, 7, 8, 9}; // A to DP
const int digitPins[3] = {11, 12, 13}; // Common cathode pins

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
  // Set segment pins as OUTPUT
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  
  // Set digit control pins as OUTPUT
  for (int i = 0; i < 3; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], HIGH); // Start with all digits off
  }

  Serial.begin(9600);
  sensors.begin();

}

void displayNumber(int number) {
  int digitValues[3] = {number / 100, (number / 10) % 10, number % 10};

  for (int i = 0; i < 3; i++) {
    digitalWrite(digitPins[i], LOW); // Enable digit

    showSegments(digits[digitValues[i]]); // Show corresponding number
    
    delay(5); // Small delay for persistence of vision
    
    digitalWrite(digitPins[i], HIGH); // Disable digit
  }
}

void showSegments(byte segments) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(segmentPins[i], (segments >> i) & 1);
  }
}

float GetTemperature(){
    sensors.requestTemperatures();
    float Celsius = sensors.getTempCByIndex(0);
    float Fahrenheit = sensors.toFahrenheit(Celsius);
    return Fahrenheit;
}



void loop() {
  float tempF = GetTemperature();
  Serial.print("Fahrenheit: ");
  Serial.print(tempF);
  Serial.print("\n");
  delay(1000);
  /*for (int i = 0; i <= 999; i++) { // Count from 0 to 999
    unsigned long start = millis();
    while (millis() - start < 200) { // Show each number for 200ms
      displayNumber(i);
    }
  }*/
}
