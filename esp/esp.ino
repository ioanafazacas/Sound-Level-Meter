#include <Wire.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
const char *SSID="ajhsdvdah";
const char *PASS="djhuijdbk";

int pinSenzor= 0;
int pinSlave=0x1A;
WiFiServer server(80);

const String SETUP_INIT = "SETUP: Initializing ESP32 dev board";
const String SETUP_ERROR = "!!ERROR!! SETUP: Unable to start SoftAP mode";
const String SETUP_SERVER_START = "SETUP: HTTP server started --> IP addr: ";
const String SETUP_SERVER_PORT = " on port: ";
const String INFO_NEW_CLIENT = "New client connected";
const String INFO_DISCONNECT_CLIENT = "Client disconnected";


const String HTTP_HEADER = "HTTP/1.1 200 OK\r\nContent-type:text/html\r\n\r\n";
const String HTML_WELCOME = "<h1>Welcome to your ESP32 Web Server!</h1>";


int val=0;

// Master
//  citeste datele de la senzorul de temperatura si le transmite la ESP32 (slave) 
//  ESP32 le trimite datele catre interfata , acesta trimite la Arduino (master) semnale 
// primite de catre butoanele din pagina web care trebuie sa faca ceva
void setup() {
  // put your setup code here, to run once: 
  Serial.begin(9600);
  Wire.begin(pinSlave);

  //pinMode(pinSenzor, OUTPUT);

  if (!WiFi.softAP(SSID, PASS)) {
    Serial.println(SETUP_ERROR);
    // Blocheaza in ciclu infinit daca nu se poate porni punctul de acces
    while (1)
    ;
  }

  const IPAddress accessPointIP = WiFi.softAPIP();
  const String serverInfoMessage = "Server started " + accessPointIP.toString()
  + " on port ";
  // Pornire server
  server.begin();
  Serial.println(serverInfoMessage);
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.onReceive(receiveEvent);
  
  WiFiClient client = server.available();

  if(client){
    String currentLine = "";
    while(client.connected()){
      if(client.available()){
        client.println(val);
        Serial.println(val);
      }
    }
  }
  delay(100);
}

void printWelcomePage(WiFiClient client) {
// Răspunsul către client trebuie să conțină headerele corecte
client.println(HTTP_HEADER);
// Trimitem mesajul HTML
client.print(HTML_WELCOME);
// Răspunsul HTTP se termină cu o linie goală
client.println();
}

void receiveEvent(int bytes){
  //val = Wire.read();
  byte highByte = Wire.read();   // Citește primul octet
  byte lowByte = Wire.read();    // Citește al doilea octet

  val = (highByte << 8) | lowByte;
}
