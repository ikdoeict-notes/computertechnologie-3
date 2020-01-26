# include <SPI.h>
# include <Ethernet2.h>

# define LED1 2
# define LED2 3
# define LED3 4
# define LED4 5

int nrLED;
bool statusLED;
String readString;
bool statusOn;
bool statusOff;

byte  mac[] = {0x90, 0xA2, 0xDA, 0x10, 0xAF, 0xBC };
IPAddress ip;
EthernetServer server (80); // server  port

void setup(){
  pinMode(LED1 , OUTPUT); //  output
  pinMode(LED2 , OUTPUT); //  output
  pinMode(LED3 , OUTPUT); //  output
  pinMode(LED4 , OUTPUT); //  output
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
          if(readString.substring (6,10) == "LED=") {
            nrLED = readString.charAt (10) - 0x30;
            statusLED = bool(readString.charAt(14) - 0x30);
            digitalWrite(nrLED, statusLED);
            }
            Serial.print(readString.substring(16,18));
           if(readString.substring(16,18) == "A=") {
            Serial.println("a detected");
            if(readString.charAt(18) == '1'){
              allLedsOn();
            }
            if(readString.charAt(18) == '0'){
              allLedsOff();
            }
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

            client.print("<input type=checkbox ");
            if(digitalRead(LED4)) client.print("checked ");
            client.print("onclick=location.href='/?LED=");
            client.print(LED4, DEC);
            client.print("&S=");
            if(! digitalRead(LED4)) client.print("1");//  togglen  bij  volgende  click
            else client.print("0");
            client.println("'>LED4 </>");

            client.print("<input type=checkbox ");
            if(digitalRead(LED3)) client.print("checked ");
            client.print("onclick=location.href='/?LED=");
            client.print(LED3, DEC);
            client.print("&S=");
            if(! digitalRead(LED3)) client.print("1");//  togglen  bij  volgende  click
            else client.print("0");
            client.println("'>LED3 </>");
            
            client.print("<input type=checkbox ");
            if(digitalRead(LED2)) client.print("checked ");
            client.print("onclick=location.href='/?LED=");
            client.print(LED2, DEC);
            client.print("&S=");
            if(! digitalRead(LED2)) client.print("1");//  togglen  bij  volgende  click
            else client.print("0");
            client.println("'>LED2 </>");

            client.print("<input type=checkbox ");
            if(digitalRead(LED1)) client.print("checked ");
            client.print("onclick=location.href='/?LED=");
            client.print(LED1, DEC);
            client.print("&S=");
            if(! digitalRead(LED1)) client.print("1");//  togglen  bij  volgende  click
            else client.print("0");
            client.println("'>LED1 </>");
            client.println("<BR/><BR/>");

            client.print("alle leds: ");
            client.print("<input type=button value='aan' onclick=location.href='/?LED=");
            client.print(statusOn, DEC);
            client.println("&S=1&A=1'>");
            client.print("<input type=button value='uit' onclick=location.href='/?LED=");
            client.print(statusOff, DEC);
            client.print("&S=0&A=0'>");

            if(statusOn) {
              statusOn = false;
              client.print("alle leds aan");
              allLedsOn();
            }
            else if (statusOff){
              statusOff = false;
              client.print("alle leds uit");
              allLedsOff();
            }
            
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
  }

void allLedsOn () {
  Serial.print("all leds on");
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
}

void allLedsOff () {
  Serial.print("all leds off");
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);

}
        
