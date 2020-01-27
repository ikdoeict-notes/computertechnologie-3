#include <Arduino.h>

int myLeds[] = {0,3};
int lichtSensor = A5;
int base = 137;

void setup() {
  for (unsigned int i = 0; i < sizeof(myLeds); i++){
    pinMode(myLeds[i], OUTPUT);
  }
  pinMode(lichtSensor, INPUT);
  Serial.begin(9600);
  Serial.println("Arduino ready");
}

void rolluikDicht(){
  digitalWrite(myLeds[1], LOW);
  digitalWrite(myLeds[0], HIGH);
}

void rolluikOpen(){
  digitalWrite(myLeds[0], LOW);
  digitalWrite(myLeds[1], HIGH);
}

void loop() {
  Serial.println(analogRead(lichtSensor));
  if(analogRead(lichtSensor) < base - 35){
    rolluikDicht();
  }
  if(analogRead(lichtSensor) > base + 35){
    rolluikOpen();
  }
}
