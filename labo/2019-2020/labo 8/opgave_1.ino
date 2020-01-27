#include<SPI.h>
#include<Ethernet2.h>

#define potentio A5

boolean ledsAan;
byte mac[] = {0x90, 0xA2, 0xDA, 0x10, 0xAF, 0xE0};

int value = 0;
int maxi = 1025;

IPAddress ip;

EthernetServer server (80);

void setup() {
  Ethernet.begin(mac);
  Serial.begin (9600);
  Serial.print("server  is at ");
  ip = Ethernet.localIP();
  Serial.println(Ethernet.localIP());
  //  start  the  Ethernet  connection  and  the↘→server:
  server.begin ();

}

void loop(){
      value = analogRead(potentio);
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
        client.println();
      }
      client.println("<TITLE>html</TITLE>");
      client.println("<meta http-equiv='refresh' content='1'></HEAD>");
      client.println("<BODY><H1>hello</H1>");
      client.print("<PROGRESS value='");
      client.print(value);
      client.print("' max='");
      client.print(maxi);
      client.println("'></PROGRESS>");
      }
      client.println("</BODY></html>");
      delay (1);//  close  the  connection:
      client.stop();
      Serial.println("client  disconnected");
      }
    }
}
