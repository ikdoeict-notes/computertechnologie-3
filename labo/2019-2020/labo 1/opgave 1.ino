# include <Arduino.h>

# define LED1 8 // LED op pin 8
# define LED2 7 //LED op pin 7
# define K2 2 // pin 2 = INT0
# define K1 3 // pin 3 = INT1

boolean interruptActive = true;

void ledToggle () {
  delay(50);
  digitalWrite(LED1, !digitalRead(LED1));
  delay(50); //dender
}

void intToggle () {
  if (interruptActive){
    detachInterrupt(digitalPinToInterrupt ( K1 ));
    digitalWrite(LED2, LOW);
    interruptActive = false;
  }
  else {
    attachInterrupt ( digitalPinToInterrupt ( K1 ) , ledToggle , FALLING ) ;
    digitalWrite(LED2, HIGH);
    interruptActive = true;
  }
  delay(50);
}

void setup () {
  pinMode ( K1 , INPUT_PULLUP ) ; // pin 2 input
  pinMode ( K2 , INPUT_PULLUP ) ;
  pinMode ( LED1, OUTPUT ) ;
  pinMode ( LED2, OUTPUT ) ;
  digitalWrite(LED1, LOW);

  attachInterrupt ( digitalPinToInterrupt ( K1 ) , ledToggle , FALLING ) ;
  attachInterrupt ( digitalPinToInterrupt ( K2 ) , intToggle , FALLING ) ;

}

void loop () {}
