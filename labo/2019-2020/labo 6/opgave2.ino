#include<SPI.h>
#include<Ethernet2.h>

boolean ledsAan;
byte mac[] = {0x90, 0xA2, 0xDA, 0x10, 0xAF, 0xE0};

EthernetServer server (80);

void setup() {
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(2), zetLedsAan, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), zetLedsUit, FALLING);
  
  Serial.begin (9600);
  //  start  the  Ethernet  connection  and  the↘→server:
  Ethernet.begin(mac);
  server.begin ();
  Serial.print("server  is at ");
  Serial.println(Ethernet.localIP());
}

void loop(){
  //  listen  for  incoming  clients
  EthernetClient client = server.available();
  if(client) {
    Serial.println("new  client");
    
  // an http  request  ends  with a blankline
  while(client.connected ()) {
    if(client.available ()) {
      char c = client.read();
      Serial.write(c);
      if(c == '\n') {
        client.println("HTTP /1.1  200 OK");
        client.println("Content -Type: text/html");
      }
      client.println("<TITLE>html</TITLE>");
      client.println("<meta http-equiv='refresh' content='1'></HEAD>");
      client.println("<BODY><H1>hello</H1>");
      if (ledsAan){
        client.println("<H2>De leds zijn aan</H2></BODY>");
      }
      if (!ledsAan){
        client.println("<H2>De leds zijn uit</H2></BODY");
      }
      }
      client.println(" </html >");
      delay (1);//  close  the  connection:
      client.stop();
      Serial.println("client  disconnected");
      }
    }
}

void zetLedsAan(){
  ledsAan = true;
  digitalWrite(4, HIGH);
  digitalWrite(6, HIGH);
}

void zetLedsUit(){
  ledsAan = false;
  digitalWrite(4, LOW);
  digitalWrite(6, LOW);
}
