# include <Arduino.h>

void setup() {
  /*
   * Serial speed 115200
   * 115200 baudes
   * 8databits
   * None (could also be E for Even Parity)
   * 2bits
   */
  Serial.begin(115200, SERIAL_8N2);
  Serial.print("Elian Van Cutsem");
}

void loop() {
}
