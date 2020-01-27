#include <Arduino.h>

# define K1 2 //knop op pin 2
# define sensor A5 //lichtsensor op A5
int myLeds[] = {2, 0}; //Leds op pin 1 en 0
int base = 137;
int nr = 0;
int minimum = 700;
int maximum = 0;
int gemiddelde = 0;
unsigned int gemiddeldeResult;
String situatie;

byte waarden[1500];
bool clicked;

void fillSituatie(){
  if(gemiddeldeResult < 130){
    situatie = "bewolkt";
  }
  if(gemiddeldeResult > 140 && gemiddelde < 330){
    situatie = "afwisselend";
  }
  if(gemiddeldeResult > 330){
    situatie = "helder";
  }
}

void output(){
  clicked = true;
  if (clicked){
  Serial.print("Aantal: ");
  Serial.println(sizeof(waarden));
  Serial.print("Minimum: ");
  Serial.println(minimum);
  Serial.print("Maximum: ");
  Serial.println(maximum);
  Serial.print("Gemiddelde: ");
  Serial.println(gemiddeldeResult);
  fillSituatie();
  Serial.println(situatie);
  Serial.println("");
  delay(100);
  }
}

void setup() {
  pinMode(K1, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Arduino Ready");
  attachInterrupt(digitalPinToInterrupt(K1), output, RISING);
}

void berekenGemiddelde() {
  gemiddeldeResult = (maximum + minimum) / 2;
}

void loop() {
    int data = analogRead(sensor);
    waarden[nr] = (byte) data;
    nr++;
    berekenGemiddelde();
    if (nr >= 1500){
      nr = 0;
    }
    if( data < minimum){
      minimum = data;
    }
    if(data > maximum){
      maximum = data;
    }
    clicked = false;
}
