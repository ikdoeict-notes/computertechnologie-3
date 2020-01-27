# include <Arduino.h>

# define LED1 8 // LED op pin 8
# define LED2 7 //LED op pin 7
# define K2 2 // pin 2 = INT0
# define K1 3 // pin 3 = INT1

int aantalK1;
boolean K1Active = false;

void teller () {
  delay(100);
  K1Active = true;
  if (K1Active){
    aantalK1++ ;
    Serial.println(aantalK1);
  }
  delay(50); //dender
  }

void resetTeller () {
  aantalK1 = 0;
}

void setup () {
  Serial.begin(9600);
  Serial.println("Hello");
  pinMode ( K1 , INPUT_PULLUP ) ; // pin 2 input
  pinMode ( K2 , INPUT_PULLUP ) ;
  pinMode ( LED1, OUTPUT ) ;
  pinMode ( LED2, OUTPUT ) ;
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

  aantalK1 = 0;

  attachInterrupt ( digitalPinToInterrupt ( K1 ) , teller , FALLING ) ;
  attachInterrupt ( digitalPinToInterrupt ( K2 ) , resetTeller , FALLING ) ;

  }

void loop () {
  delay(100);
  K1Active = false;
  delay(100);
 }
