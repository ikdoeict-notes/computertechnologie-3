#include <Arduino.h>

int myLeds[] = {7, 2, 3, 4};
int lichtSensor = A5;
int maximum = 700;
int base = maximum / 5;
int meting;

void setup() {
  // put your setup code here, to run once:
  for (unsigned int i = 0; i < sizeof(myLeds); i++){
    pinMode(myLeds[i], OUTPUT);
  }
  pinMode(lichtSensor, INPUT);
  Serial.begin(9600);
  Serial.println("Arduino ready");
}

void loop() {
  meting = analogRead(lichtSensor);
  Serial.println(meting);

  for (int i = 6; i <= 9; i++){
    if(i > meting/140 + 5){
        digitalWrite(i, HIGH);
    }
    else{
        digitalWrite(i, LOW);
    }
  }
}
