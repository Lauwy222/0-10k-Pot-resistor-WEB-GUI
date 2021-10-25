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
            client.println("
.slidecontainer {
  width: 100%;
}

.slider {
  -webkit-appearance: none;
  width: 100%;
  height: 15px;
  border-radius: 5px;
  background: #d3d3d3;
  outline: none;
  opacity: 0.7;
  -webkit-transition: .2s;
  transition: opacity .2s;
}

.slider:hover {
  opacity: 1;
}

.slider::-webkit-slider-thumb {
  -webkit-appearance: none;
  appearance: none;
  width: 25px;
  height: 25px;
  border-radius: 50%;
  background: #04AA6D;
  cursor: pointer;
}

.slider::-moz-range-thumb {
  width: 25px;
  height: 25px;
  border-radius: 50%;
  background: #04AA6D;
  cursor: pointer;
}
            ");
            client.println("</style></head>");
            
            
            client.println("<title>ESP-Controller-Module</title>");
            client.println("");
            client.println("");
            client.println(" ");
            client.println(" ");
            
            
            //client.println("<h2>Volume: </h2>" + volume + "%");
            
            client.println("");
            client.print("
<div class=\"slidecontainer\">
  <input type=\"range\" min=\"1\" max=\"100\" value=\"50\" class=\"slider\" id=\"myRange\">
  <p>Value: <span id=\"demo\"></span></p>
</div>

<script>
var slider = document.getElementById(\"myRange\");
var output = document.getElementById(\"demo\");
output.innerHTML = slider.value;

slider.oninput = function() {
  output.innerHTML = this.value;
}
</script>");
          
          /*  client.print("<p><a href=\"/volume/0\"><button class=\"button\">0%</button></a></p>");
            client.print("<p><a href=\"/volume/20\"><button class=\"button\">20%</button></a></p>");
            client.print("<p><a href=\"/volume/40\"><button class=\"button\">40%</button></a></p>");
            client.print("<p><a href=\"/volume/60\"><button class=\"button\">60%</button></a></p>");
            client.print("<p><a href=\"/volume/80\"><button class=\"button\">80%</button></a></p>");
            client.print("<p><a href=\"/volume/100\"><button class=\"button\">100%</button></a></p>");
            client.println("");          
               

               */
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
