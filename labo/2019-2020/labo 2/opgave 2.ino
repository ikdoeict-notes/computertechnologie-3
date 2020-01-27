# include <Arduino.h>

int myLeds[] = {6, 7, 8, 9}; //PINS CONTAINING LEDS
String optionC = "";

void setup() {
  Serial.begin(9600);

  for (unsigned int i = 0; i < sizeof(myLeds) ; i++){
    pinMode(myLeds[i], OUTPUT);
  }
  Serial.println("Toets de letter in van uw keuze:");
  Serial.println("a. alle LED’s aan");
  Serial.println("b. alle LED’s uit");
  Serial.println("c. individuele LED aansturen");
}

void ledsAan() {
  for (unsigned int i = 0; i < sizeof(myLeds); i++){
    digitalWrite(myLeds[i], HIGH);
  }
  Serial.println("alle leds aan");
}
void ledsUit() {
  for (unsigned int i = 0; i < sizeof(myLeds); i++){
    digitalWrite(myLeds[i], LOW);
  }
  Serial.println("alle leds uit");
}

void loop() {
  while (Serial.available()) {
     char inChar = (char)Serial.read();
     String inputString = "";
     inputString += inChar;
     optionC += inChar;
     if (inputString.equals("a")){
        optionC = "";
        ledsAan();
     }
     if (inputString.equals("b")){
        optionC = "";
        ledsUit();
     }
     if (inputString.equals("c")){
      for (int i = 0 ; i < (int) optionC.length(); i++){
        optionC.substring(i, i+1);
        if(optionC.substring(i, i+1).equals("A")){
          digitalWrite(myLeds[optionC.substring(i-1, i).toInt()-1], HIGH);
        }
        if(optionC.substring(i, i+1).equals("U")){
          digitalWrite(myLeds[optionC.substring(i-1, i).toInt()-1], LOW);
        }
      }
      optionC = "";
     }
   }
}
