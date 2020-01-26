#include <Arduino.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(9, 8, 5, 4, 3, 2);
String message = "Dit is een heel lang bericht.";

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  lcd.print(message);
  for (unsigned int positionCounter = 0; positionCounter < message.length(); positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(300);
  }

  lcd.clear();

  for (int i = 0 ; i < 3 ; i++){
    lcd.print("flikker");
    delay(200);
    lcd.clear();
    delay(200);
  }
}
