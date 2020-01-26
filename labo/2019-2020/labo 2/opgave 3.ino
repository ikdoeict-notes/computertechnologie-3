# include <Arduino.h>

int myLeds[] = {2, 3, 4, 5}; //PINS CONTAINING LEDS

void setup() {
  for (int i = 0 ; i < 4 ; i++){
    pinMode(myLeds[i], OUTPUT);
  }
  Serial.begin(9600);
  Serial.println("Arduino is ready"); //debug
  Serial.println("Stuur een getal tussen 0 en 9999:");
}

void ledFlikker(int aantalFlikkeringen){
  for (int i = 0 ; i < aantalFlikkeringen * 2 ; i++){
    for (int j = 0 ; j < 4 ; j++){
      digitalWrite(myLeds[j], !digitalRead(myLeds[j]));
    }
    delay(200);
  }
}

void resetLeds(){
    for (int i = 0 ; i < 4 ; i++){
      digitalWrite(myLeds[i], LOW);
    }
}

void getalGestuurd(int getal){
  if(getal > 0 && getal <= 9){
    resetLeds();
    digitalWrite(myLeds[0], HIGH);
  }
  if(getal > 9 && getal < 100){
    resetLeds();
    digitalWrite(myLeds[1], HIGH);
  }
  if(getal >= 100 && getal <= 999){
    resetLeds();
    digitalWrite(myLeds[2], HIGH);
  }
  if(getal >= 1000 && getal <= 9999){
    resetLeds();
    digitalWrite(myLeds[3], HIGH);
  }
  if(getal > 9999){
    resetLeds();
    ledFlikker(3);
  }
}

void loop() {
  while (Serial.available() == 0);
    int inputGetal = Serial.parseInt();
    getalGestuurd(inputGetal);
}
