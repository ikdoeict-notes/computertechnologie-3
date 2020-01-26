#include <Arduino.h>

# define sensor A5 //sensor on pin A5

unsigned long startTime;
unsigned long currentTime;
long conversionTime;

void setup() {
  startTime = micros();
  analogReference(INTERNAL);
  pinMode(sensor, INPUT);
  Serial.begin(9600);
  Serial.println("Arduino Ready");

  currentTime = micros();
  Serial.println("Sensor leest: " + (String)analogRead(sensor));
  Serial.print("conversie duurde: ");
  conversionTime = currentTime - startTime;
  Serial.print((String)conversionTime);
}

void loop() {
}
