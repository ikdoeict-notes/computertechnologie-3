#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet2.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp2.h>
#include <Twitter.h>
#include <util.h>

int myLeds[] = {2, 4, 6, 8}; //PINS CONTAINING LEDS
String optionC = "";
byte mac[] = {  
  0x90, 0xA5, 0xDA, 0x10, 0xAF, 0xBF };
EthernetServer server (23);

void setup() {
  for (int i = 0; i < sizeof(myLeds) ; i++){
    pinMode(myLeds[i], OUTPUT);
  }
  
  Serial.begin(9600);
  Serial.println("Arduino Ready");

  if(Ethernet.begin(mac)){
    Serial.print("ip is: ");
    Serial.println(Ethernet.localIP());
  }

  server.begin();
}

void loop() {
  EthernetClient client = server.available();
  
  if(client) {
    Serial.println("client connected");
    client.println("Toets de letter in van uw keuze:");
    client.println("a. alle LED’s aan");
    client.println("b. alle LED’s uit");
    client.println("c. individuele LED aansturen");
    while(client.connected()) {
      if(client.available() > 0) {
        char inChar = (char) client.read();
        String inputString = "";
        inputString += inChar;
        Serial.write(inChar);
        if (inputString.equals("a")){
          optionC = "";
          ledsAan();
        }
        if (inputString.equals("b")){
          optionC = "";
          ledsUit();
        }
        if (inputString.equals("q")){
          optionC = "";
          Serial.println("a client is disconnecting.");
          client.println("disconnecting..");
          client.stop();
        }
      } 
    }
    Serial.print("Connectie  verloren");
  }
}
void ledsAan(){
  for (int i = 0 ; i < sizeof(myLeds) ; i++){
    digitalWrite(myLeds[i], HIGH);
  }
}

void ledsUit(){
  for (int i = 0 ; i < sizeof(myLeds) ; i++){
    digitalWrite(myLeds[i], LOW);
  }
}
