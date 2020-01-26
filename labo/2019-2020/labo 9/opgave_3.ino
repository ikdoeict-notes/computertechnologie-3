//includes
# include <SPI.h>
# include <Ethernet2.h>

//defines
# define LED1 3
# define LED2 5
# define LED3 6

//variables
int nrLED;
String readString;
int valueLed3 = 0;

//ethernet
byte  mac[] = {0x90, 0xA2, 0xDA, 0x10, 0xAF, 0xBC };
IPAddress ip;
EthernetServer server (80); // server  port

void setup(){
  pinMode(LED1 , OUTPUT); //  output
  pinMode(LED2 , OUTPUT); //  output
  pinMode(LED3 , OUTPUT); //  output
  
  Ethernet.begin(mac);
  // start  Ethernet  en  server
  Serial.begin (9600);
  Serial.print("server  is at ");
  ip = Ethernet.localIP();
  Serial.println(Ethernet.localIP());
  
  delay(1000);
  server.begin();
}

void loop(){
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        //karakter  per  karakter  lezen
        if(readString.length () < 100) {
          readString += c;

        }
        // einde  HTTP  request
        if(c == '\n') {
           }
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println();
            client.println("<HTML>");
            client.println("<HEAD>");
            client.println("<TITLE>Arduino LED besturing</TITLE>");
            client.println("</HEAD>");
            client.println("<BODY>");
            client.println("<H1>LED besturing</H1>");
            
            client.println("<br><br>");

            client.println("<LABEL>LED1</LABEL><input type=range onchange=location.href=\"/?LED=1&V=\"+this.value min=\"0\" max=\"255\" value=\"0\" /><BR><BR>");
            client.println("<LABEL>LED2</LABEL><input type=range onchange=location.href=\"/?LED=2&V=\"+this.value min=\"0\" max=\"255\" value=\"0\" /><BR><BR>");
            
            client.print("<LABEL>LED3</LABEL><INPUT type=range onchange=location.href=\"/?LED=3&V=");
            client.print(valueLed3);
            client.print("\" min=\"0 max=\"255\" value=\"");
            client.print(valueLed3);
            client.println("\" /><BR>");
            analogWrite(LED3, valueLed3);
            
            client.println("</BODY>");
            client.println("</HTML>");
            delay (1);
            //stop  client  zodat  pagina  herladen  wordt
            client.stop();
            // string  wissen
            readString="";
            }
          }
        }
      }        
