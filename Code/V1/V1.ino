#include <ESP8266WiFi.h>
const char* ssid     = "HP-OMEN-015"; //Enter network SSID 
const char* password = "0613974488"; //Enter network PASSWORD 

WiFiServer server(80);
String header;
String volume = "0"; 

void connectToWifi(){
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void setup() {
  Serial.begin(115200);
  connectToWifi(); 
}
  void volume0(){
  volume = "0";
  Serial.println("Volume=" + volume + "%");
}
  void volume20(){
  volume = "20";
  Serial.println("Volume=" + volume + "%");
}
  void volume40(){
  volume = "40";
  Serial.println("Volume=" + volume + "%");
}
  void volume60(){
  volume = "60";
  Serial.println("Volume=" + volume + "%");
}
  void volume80(){
  volume = "80";
  Serial.println("Volume=" + volume + "%");
}
  void volume100(){
  volume = "100";
  Serial.println("Volume=" + volume + "%");
}



void createWebServer(){
  WiFiClient client = server.available();   
  if (client) {                            
    Serial.println("New Client.");        
    String currentLine = "";               
    while (client.connected()) {           
      if (client.available()) {          
        char c = client.read();            
        Serial.write(c);                 
        header += c;
        if (c == '\n') {                 
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

              if (header.indexOf("GET /volume/0") >= 0) {
              volume0();
              } else if (header.indexOf("GET /volume/20") >= 0) {
              volume20();
              } else if (header.indexOf("GET /volume/40") >= 0) {
              volume40();
              } else if (header.indexOf("GET /volume/60") >= 0) {
              volume60();
              } else if (header.indexOf("GET /volume/80") >= 0) {
              volume80();
              } else if (header.indexOf("GET /volume/100") >= 0) {
              volume100();
              } 
            
            
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
           
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #2ca545; border: none; color: white; padding: 16px 40px; margin: 25px; box-shadow: 0px 0px 15px 1px #aaaaaa;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".buttoncenter { background-color: #ba1e1e;}");
            client.println("</style></head>");
            
            
            client.println("<title>ESP-Controller-Module</title>");
            client.println("");
            client.println("");
            client.println(" ");
            client.println(" ");
            
            
            //client.println("<h2>Volume: </h2>" + volume + "%");
            
            client.println("");
            client.print("<p><a href=\"/volume/0\"><button class=\"button\">0%</button></a></p>");
            client.print("<p><a href=\"/volume/20\"><button class=\"button\">20%</button></a></p>");
            client.print("<p><a href=\"/volume/40\"><button class=\"button\">40%</button></a></p>");
            client.print("<p><a href=\"/volume/60\"><button class=\"button\">60%</button></a></p>");
            client.print("<p><a href=\"/volume/80\"><button class=\"button\">80%</button></a></p>");
            client.print("<p><a href=\"/volume/100\"><button class=\"button\">100%</button></a></p>");
            client.println("");          
               
            client.println("</body></html>");
            
            
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') { 
          currentLine += c;    
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void loop(){
  createWebServer();
}
