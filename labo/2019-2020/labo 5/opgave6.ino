#include <Wire.h>
#define TMP102_I2C_ADDRESS 72

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), oneShot, FALLING);
  Wire.begin(); // start the I2C library
  Serial.begin(9600); 
  Serial.println("Arduino Ready");
  setConf();
}

void oneShot(){
  Wire.beginTransmission(TMP102_I2C_ADDRESS); //Say hi to the sensor.
  Wire.write(0x01);
  Wire.write(B11100001);
  Wire.write(B10110000);
  Wire.endTransmission();
}

void setConf(){
   Wire.beginTransmission(TMP102_I2C_ADDRESS); //Say hi to the sensor.
  Wire.write(0x02);
  Wire.write(14); //TLOW
  Wire.endTransmission();
  
  Wire.beginTransmission(TMP102_I2C_ADDRESS); //Say hi to the sensor.
  Wire.write(0x03); //THIGH
  Wire.write(15);
  Wire.endTransmission();

  Wire.beginTransmission(TMP102_I2C_ADDRESS); //Say hi to the sensor.
  Wire.write(0x01);
  Wire.write(B01100001);
  Wire.write(B10110000);
  Wire.endTransmission();
  
}

void getTemp(){
  byte firstbyte, secondbyte;
  int val; 
  float convertedtemp; 
  float correctedtemp;

  Wire.beginTransmission(TMP102_I2C_ADDRESS); //Say hi to the sensor.
  Wire.write(0x00);
  Wire.requestFrom(TMP102_I2C_ADDRESS, 2);
  Wire.endTransmission();
 
  firstbyte = (Wire.read());
  secondbyte = (Wire.read());
    val = ((firstbyte) << 4);  
    val |= (secondbyte >> 4);    
    convertedtemp = val*0.0625;
    correctedtemp = convertedtemp; 
 
  Serial.print(correctedtemp);
  Serial.println("°C");
}

void getTempEM() {
  byte firstbyte, secondbyte;
  int val; 
  float convertedtemp; 
  float correctedtemp;

  Wire.beginTransmission(TMP102_I2C_ADDRESS); //Say hi to the sensor.
  Wire.write(0x00);
  Wire.requestFrom(TMP102_I2C_ADDRESS, 2);
  Wire.endTransmission();
 
  firstbyte = (Wire.read());
  secondbyte = (Wire.read());
    val = ((firstbyte) << 5);  
    val |= (secondbyte >> 3);    
    convertedtemp = val*0.0625;
    correctedtemp = convertedtemp; 
 
  Serial.print(correctedtemp);
  Serial.println("°C"); 
}
 
void loop() {
  if (digitalRead(5) == LOW){
    Wire.beginTransmission(TMP102_I2C_ADDRESS); //Say hi to the sensor.
  Wire.write(0x01);
  Wire.write(B11100001);
  Wire.write(B10110000);
  Wire.endTransmission();
  }
  getTempEM();
  //getTemp();
  delay(500);
}
