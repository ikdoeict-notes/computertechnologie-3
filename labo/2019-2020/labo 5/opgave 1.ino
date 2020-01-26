#include "Arduino.h"
#include "Wire.h"

#define TMP102_I2C_ADDRESS 72

void setup() {
  Wire.begin(); // start the I2C library
  Serial.begin(9600);
  Serial.println("Arduino Ready");
}

void getTemp(){
  byte firstbyte, secondbyte;
  int val;
  float convertedtemp;
  float correctedtemp;

  Wire.beginTransmission(TMP102_I2C_ADDRESS); //Say hi to the sensor.
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(TMP102_I2C_ADDRESS, 2);
  Wire.endTransmission();


  firstbyte = (Wire.read());
  secondbyte = (Wire.read());
    val = ((firstbyte) << 4);
    val |= (secondbyte >> 4);
    convertedtemp = val*0.0625;
    correctedtemp = convertedtemp - 5;

  Serial.print("firstbyte is ");
  Serial.print("\t");
  Serial.println(firstbyte, BIN);
  Serial.print("secondbyte is ");
  Serial.print("\t");
  Serial.println(secondbyte, BIN);
  Serial.print("Concatenated byte is ");
  Serial.print("\t");
  Serial.println(val, BIN);
  Serial.print("Converted temp is ");
  Serial.print("\t");
  Serial.println(val*0.0625);
  Serial.print("Corrected temp is ");
  Serial.print("\t");
  Serial.println(correctedtemp);
  Serial.println();
}

void loop() {
  getTemp();
  delay(1000); //wait 5 seconds before printing our next set of readings.
}
