#include<SPI.h>
#include<Ethernet2.h>
#include<PubSubClient.h>

bool test = true;

byte  mac []={0x90, 0xA2, 0xDA, 0x10, 0xAF, 0xAE};
IPAddress  ip(10, 128, 100, 45);
IPAddress  server (10, 128, 100, 57);

//broker
void callback(char* topic , byte* payload, unsigned int length) {
  Serial.print("Message  arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  for(int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
    }
  Serial.println ();
}
    
EthernetClient ethClient;
PubSubClient client(ethClient);

void reconnect() {
  // Loop  until we’re  reconnected
  while(! client.connected ()) {
    Serial.print("Attempting  MQTT  connection...");
    //Attempt  to  connect
    if(client.connect("ElianVanCutsem")) {
      Serial.println("connected");     
      if(test){
        test = false; 
        client.publish("labo/elianvancutsem/test","helloWorld met groetjes van Elian");
      }
      client.subscribe("inTopic");
      }
      else{
        Serial.print("failed , rc=");
        Serial.print(client.state ());
        Serial.println(" try  again  in 5 seconds");
        // Wait 5 seconds  before  retrying
        delay (5000);
      }
  }
}

void setup() {
  Serial.begin (57600);
  
  client.setServer(server , 1883);
  client.setCallback(callback);
  
  Ethernet.begin(mac , ip);
  //  Allow  the  hardware  to sort  itself  out
  delay (1500);
}

void loop() {
  if(!client.connected()) {
    reconnect ();
    }
    client.loop();
}
      
    
