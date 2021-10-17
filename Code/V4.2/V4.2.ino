/*
 * COMPILE IN `115200` BAUDRATE
 */

#include <ESP8266WiFi.h>
const char* ssid     = "HP-OMEN-015"; //Enter network SSID 
const char* password = "0613974488"; //Enter network PASSWORD 

WiFiServer server(80);
String header;
String volume = "0"; 
String vu0 = "<th class=\"vuwhite\">";
String vu1 = "<th class=\"vuwhite\">";
String vu2 = "<th class=\"vuwhite\">";
String vu3 = "<th class=\"vuwhite\">";


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

//Volume
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

//VU


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

            if (header.indexOf("GET /vu/3/1") >= 0) {
              vu3 = "<th class=\"vugreen\">";
              } else if (header.indexOf("GET /vu/3/0") >= 0) {
              vu3 = "<th class=\"vuwhite\">";
              }
            if (header.indexOf("GET /vu/2/1") >= 0) {
              vu2 = "<th class=\"vugreen\">";
              } else if (header.indexOf("GET /vu/2/0") >= 0) {
              vu2 = "<th class=\"vuwhite\">";
              }
            if (header.indexOf("GET /vu/1/1") >= 0) {
              vu1 = "<th class=\"vuyellow\">";
              } else if (header.indexOf("GET /vu/1/0") >= 0) {
              vu1 = "<th class=\"vuwhite\">";
              }
            if (header.indexOf("GET /vu/0/1") >= 0) {
              vu0 = "<th class=\"vured\">";
              } else if (header.indexOf("GET /vu/0/0") >= 0) {
              vu0 = "<th class=\"vuwhite\">";
              }
            
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
           
            client.println("<style>");
            client.println("table {  border-collapse: collapse;  width: 100%;}");
            client.println("th, td {  padding: 3vh;  text-align: center;  border: 1px solid rgb(0, 0, 0);}");
            client.println("tr {background-color: white;}");
            
            client.println(".vuwhite{ background-color: white;}");
            client.println(".vugreen { background-color: green;}");
            client.println(".vuyellow{ background-color: yellow;}");
            client.println(".vured{ background-color: red;}");
            
            client.println(".btn-group:after {content: \"\"; clear: both; display: table;}");
            client.println(".btn-group button:not(:last-child) {border-right: none;}");
            client.println(".btn-group button:hover {background-color: #3e8e41;}");
            client.println(".btn-group button {background-color: #04AA6D; border: 1px solid green; color: white; padding: 3vh; cursor: pointer; width: 100%; display: block; }");
            client.println("@media only screen and (min-height: 638px){  .minexceed{    display:none;  }}");
            client.println("@media only screen and (max-height: 638px){  .btn-group{display: none;}}");
            client.println(".callout {  max-width: 100%;  min-width: 100%;}");
            client.println(".callout-header {  padding: 25px 15px;  background: rgb(236, 17, 17);  font-size: 30px;  color: white;}");
            client.println(".callout-container {  padding: 15px;  background-color: #ccc;  color: black}");
            client.println("</style></head>");
            
            
            client.println("<title>ESP-Controller-Module</title>");
            client.println("");
            client.println("");
            client.println(" ");
            client.println(" ");
            
            
            //client.println("<h2>Volume: </h2>" + volume + "%");
            
            client.println("");
            client.print("<table>");
            client.print("<tr>" + vu0 + "</th></tr>");
            client.print("<tr>" + vu1 + "</th></tr>");
            client.print("<tr>" + vu2 + "</th></tr>");
            client.print("<tr>" + vu3 + "</th></tr>");
            client.print("</table>");
            client.println("<br>");
            client.println("<div class=\"minexceed\"><div class=\"callout\"><div class=\"callout-header\">!Warning!</div><div class=\"callout-container\">");
            client.println("<p>You've exceeded our minimum viewheight of 638 pixels. Please use desktop mode.</p>");
            client.println("</div></div></div>");
            client.println("<div class=\"btn-group\" style=\"width:100%\">");
            client.print("<p><a href=\"/volume/0\"><button>0%</button></a></p>");
            client.print("<p><a href=\"/volume/20\"><button>20%</button></a></p>");
            client.print("<p><a href=\"/volume/40\"><button>40%</button></a></p>");
            client.print("<p><a href=\"/volume/60\"><button>60%</button></a></p>");
            client.print("<p><a href=\"/volume/80\"><button>80%</button></a></p>");
            client.print("<p><a href=\"/volume/100\"><button>100%</button></a></p>");
            client.println("</div>");
            client.println("<script>");
            //client.println("var delayInMilliseconds = 1000; setTimeout(function() {location.reload();}, delayInMilliseconds);");
            client.println("Access-Control-Allow-Origin: *");
            client.println("Access-Control-Allow-Origin(*)");
            client.println("Access-Control-Allow-Origin: \"*\"");
            client.println("</script>");
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
