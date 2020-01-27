#include<SPI.h>
#include<Ethernet2.h>

byte mac[] = {0x90, 0xA2, 0xDA, 0x10, 0xAF, 0xD0};
String pElement = "";

IPAddress ip;

EthernetServer server (80);

void setup() {
  Ethernet.begin(mac);
  Serial.begin (9600);
  Serial.print("server  is at ");
  ip = Ethernet.localIP();
  Serial.println(Ethernet.localIP());
  //start the Ethernet connection and the server:
  server.begin ();
}

void loop() {

  //  listen  for  incoming  clients
  EthernetClient client = server.available();
  if(client) {
    Serial.println("new client");

    // an http  request  ends  with a blankline
    while(client.connected ()) {
      if(client.available ()) {
        char c = client.read();
        Serial.write(c);
        if(c == '\n') {
          client.println("HTTP /1.1 200 OK");
          client.println("Content -Type: text/html");
          client.println();
        }

        client.println("<TITLE>html</TITLE>");
        client.println("<meta http-equiv='refresh' content='1'></HEAD>");
        client.println("<BODY><H1>hello</H1>");
        client.print("<p>");
        client.println("</p>");
      }

      client.println("</BODY></html>");
      delay(1); //close the connection:
      client.stop();
      Serial.println("client disconnected");
      }
    }
}
