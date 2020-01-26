#include<Arduino.h>

#include<SPI.h>
#include<Ethernet2.h>
#include<PubSubClient.h>

bool test = true;

// ethernet shield mac address
byte  mac []={0x90, 0xA2, 0xDA, 0x10, 0xAF, 0xE0};

// ip of server that will be used
IPAddress  server (10, 128, 100, 71);
IPAddress ip;

#define led1 6
#define led2 8

// broker
void callback(char* topic , byte* payload, unsigned int length) {
  String topicString = "";
  topicString += topic;
  String msg = "";

  for(byte i = 0; i < length; i++) {
    msg += (char) payload[i];
    //Serial.print((char)payload[i]);
  }
  Serial.println ();

  if (topicString.equals("labo/klimaat/temp")){
    /*Serial.print(msg.toFloat());
    Serial.println("°C");*/
    Serial.print(msg.toFloat() ,1);
    Serial.println("°C");
  }
  if (msg.equals("1") && topicString.equals("labo/licht/lamp1")){
    digitalWrite(led1, HIGH);
  }
   if (msg.equals("0") && topicString.equals("labo/licht/lamp1")){
    digitalWrite(led1, LOW);
  }
  if (msg.equals("1") && topicString.equals("labo/licht/lamp2")){
    digitalWrite(led2, HIGH);
  }
   if (msg.equals("0") && topicString.equals("labo/licht/lamp2")){
    digitalWrite(led2, LOW);
  }
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
        //client.publish("labo/elianvancutsem/test","helloWorld met groetjes van Elian");
      }
      client.subscribe("labo/licht/lamp1");
      client.subscribe("labo/licht/lamp2");
      client.subscribe("labo/klimaat/temp");
      }
      else{
        Serial.print("failed , rc=");
        Serial.print(client.state ());
        Serial.println("try  again  in 5 seconds");
        // Wait 5 seconds  before  retrying
        delay (5000);
      }
  }
}

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);

  Serial.begin (57600);
  Serial.print("Arduino ready");
  client.setServer(server , 1883);
  client.setCallback(callback);

  Ethernet.begin(mac);
  ip = Ethernet.localIP();
  Serial.println(Ethernet.localIP() + " + " + ip);
  //  Allow  the  hardware  to sort  itself  out
  delay (1500);
}

void loop() {
  if(!client.connected()) {
    reconnect ();
    }
    client.loop();
}
