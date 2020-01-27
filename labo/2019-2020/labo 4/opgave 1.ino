#include <Arduino.h>
#include <LiquidCrystal.h>

void setup() {
  LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //pins
  lcd.begin(16, 2);
  lcd.print("Elian");
  lcd.setCursor(0,1);
  lcd.print("Van Cutsem");
}

void loop() {
}
