#include "Wire.h"
#include "TM1636.h"
#include <Wire.h>
#include <TimerOne.h>

TM1636 tm1636(7,8);

#define K1 9
#define K2 10
#define K3 11
#define DS1307_I2C_ADDRESS 0x68
byte seconde;
byte minuut;
byte uur;
boolean changingHour = false;
boolean changingMinute = false;
boolean changingStuff = false;
boolean point = true;
boolean showingTime = true;
boolean timeChanged = false;
unsigned char time[4];

void pciSetup(byte pin) {
  *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));
  PCIFR |= bit (digitalPinToPCICRbit(pin));
  PCICR |= bit (digitalPinToPCICRbit(pin));
}

void setup() {
  pinMode(K1, INPUT_PULLUP);
  pinMode(K2, INPUT_PULLUP);
  pinMode(K3, INPUT_PULLUP);
  tm1636.init();
  Wire.begin();
  Serial.begin(9600);
  Timer1.initialize(500000);
  Timer1.attachInterrupt(timerIsr);
  
  pciSetup(K1);
  pciSetup(K2);
  pciSetup(K3);
  getTime();
}

void loop() {
  if (timeChanged) {
   writeTime(); 
   timeChanged = false;
  }
  if (!changingStuff) {
    displayTime();
    getTime();
  }
}

void timerIsr() {
  if (showingTime) {
    tm1636.point(point);
    point = !point;
  }
}

void getTime() {
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write((byte)0x00);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
  seconde = bcdToDec(Wire.read() & 0x7f);
  minuut = bcdToDec(Wire.read());
  uur = bcdToDec(Wire.read() & 0x3f);
}

void displayTime() {
  time[0] = uur / 10;
  time[1] = uur % 10;
  time[2] = minuut / 10;
  time[3] = minuut % 10;
  tm1636.display((int8_t*)time);
}

void writeTime() {
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write((byte)0x00);
  Wire.write(decToBcd(seconde));
  Wire.write(decToBcd(minuut));
  Wire.write(decToBcd(uur));
  Wire.endTransmission();
}

byte bcdToDec(byte val) {
  return ((val/16*10) + (val%16));
}

byte decToBcd(byte val) {
  return ((val/10*16) + (val%10));
}

ISR (PCINT0_vect) {  
  unsigned long now = millis();
  unsigned long previousInt = 0;
  
  if (now - previousInt > 300) {
    if (digitalRead(K1) == LOW) {
     if (changingStuff) {
       if (changingHour) {
         if (uur > 0) {
           uur--;
           writeTime();
         }
       }
       else if (changingMinute) {
         if (minuut > 0) {
           minuut--;
           writeTime();
         }
       }
     }
   }
 }
 if (now - previousInt > 300) {
   if (digitalRead(K2) == LOW) {
     if (changingStuff) {
       if (changingHour) {
         if (uur < 23) {
           uur++;
           timeChanged = true;
         }
         else {
          uur = 0;
          timeChanged = true; 
         }
       }
       else if (changingMinute) {
         if (minuut < 59) {
           minuut++;
           timeChanged = true;
         }
         else {
           minuut = 0;
           timeChanged = true;
         }
       }
     }
   } 
 }
 if (now - previousInt > 300) {
   if (digitalRead(K3) == LOW) {
     changingStuff = true;
     showingTime = false;
     if (changingStuff && !changingHour && !changingMinute) {
       changingHour = true;
     }
     else if (changingStuff && changingHour) {
       changingHour = false;
       changingMinute = true;
     }
     else if (changingStuff && changingMinute) {
       changingMinute = false;
       changingStuff = false;
       showingTime = true;
     }
   }
 }
 previousInt = now;
 displayTime();
}
