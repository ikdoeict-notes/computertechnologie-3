#include <Arduino.h>
#include <LiquidCrystal.h>

#define CLK 7
#define DT 8

byte customChar0[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte customChar1[] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000
};

byte customChar2[] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000
};

byte customChar3[] = {
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100
};

byte customChar4[] = {
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110
};

byte customChar5[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

int percentage = 0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);

  lcd.createChar(0, customChar0);
  lcd.createChar(1, customChar1);
  lcd.createChar(2, customChar2);
  lcd.createChar(3, customChar3);
  lcd.createChar(4, customChar4);
  lcd.createChar(5, customChar5);

  lcd.begin(16, 2);
}

void loop() {
  lcd.clear();
  String displayString;
  int tempPercentage;

  if (digitalRead(CLK) == LOW){
    delay(50);
    percentage++;
  }

  if(percentage > 100){
    percentage = 100;
  }

  tempPercentage = percentage;
  lcd.print((String)percentage + "%");

  lcd.setCursor(0,1);

  for(int i = 0 ; i < percentage ; i++){
    if(tempPercentage >= 5){
      displayString += (char) 5;
      tempPercentage -= 5;
    }
   }
    if(tempPercentage >= 4){
      displayString += (char) 4;
      tempPercentage -= 4;
    }
    if(tempPercentage >= 3){
      displayString += (char) 3;
      tempPercentage -= 3;
    }
    if(tempPercentage >= 2){
      displayString += (char) 2;
      tempPercentage -= 2;
    }
    if(tempPercentage >= 1){
      displayString += (char) 1;
      tempPercentage -= 1;
    }

  lcd.print(displayString);
  delay(50);
}
