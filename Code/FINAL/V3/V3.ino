//rotary encoder
#include "KY040rotary.h"
#include <Wire.h>  

//display
#include "SSD1306.h"

//pot meter
#include <X9C.h>

//webserver
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//webpage
#include "PageIndex.h";

//AC credentials
const char* ssid = "DeltaPI";
const char* password = "lekkertjes";

//open server
ESP8266WebServer server(80);

void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

// init the button
KY040 Rotary(D5, D6, D7);
//init the display
SSD1306  display(0x3C, D2, D3);
//set & calculate values
int number = 0;
String volume = String(number, DEC);
String vol = "Volume: " + volume;

//Set pins for X9C
#define UD 15
#define INC 16
#define CS 2

X9C pot;

//KY040 button
void OnButtonClicked(void) {
  Serial.println("Button 1: clicked");
  display.init();
  display.drawString(0, 0, "Button 1: clicked");
  display.display();
}

//KY040 LEFT
void OnButtonLeft(void) {
 if(number!=0){
    --number;

    displayrendering();
    
   // pot.trimPot(1,X9C_DOWN,false);
   
  }
}

//KY040 RIGHT
void OnButtonRight(void) {
  if(number!=100){
    ++number;

    displayrendering();

  //  pot.trimPot(1,X9C_UP,false);

    
  }}

//Server handling
  void mainserver(){
  String POS = server.arg("servoPOS");
  number = POS.toInt();
  delay(15);
  
  displayrendering();
  server.send(200, "text/plane","");
  }

  //DISPLAY render
  void displayrendering(){
    //SETPOT
    pot.setPot(numer,true);
    //Calculate and transform
    volume = String(number, DEC);
    vol = "Volume: " + volume;
    //Serial MON
    Serial.println("Volume " + volume);
    Serial.println("Vol " + vol);
    //Display
    display.init();
    display.drawString(0, 0, vol);
    display.display();

    
  }
  
void setup() {
  //declare pins
  pinMode(D0, OUTPUT);//D0-1-INCREMENT/DECREMENT
  pinMode(16, OUTPUT);//D8-2-UP/DOWN
  pinMode(17, OUTPUT);//D4-7
  // open the serial port
  display.init();
  Serial.begin(115200);
  Serial.println("Starting...");
  display.drawString(0, 0, vol);
  display.display();

pot.begin(CS, INC, UD);
pot.setPotMin(false);

  if ( !Rotary.Begin() ) {
    Serial.println("unable to init rotate button");
    display.init();
    display.drawString(0, 0, "unable to init rotate button");
    display.display();
    while (1);
  }

  // init callbacks
  Rotary.OnButtonClicked(OnButtonClicked);
  Rotary.OnButtonLeft(OnButtonLeft);
  Rotary.OnButtonRight(OnButtonRight);

  Serial.println("KY-040 rotary encoder OK");

  delay(500);
  
  WiFi.softAP(ssid, password);  //--> Start Making ESP8266 NodeMCU as an access point

  IPAddress apip = WiFi.softAPIP(); //--> Get the IP server
  Serial.print("Connect your wifi laptop/mobile phone to this NodeMCU Access Point : ");
  Serial.println(ssid);
  Serial.print("Visit this IP : ");
  Serial.print(apip); //--> Prints the IP address of the server to be visited
  Serial.println(" in your browser.");

  server.on("/",handleRoot);  //--> Routine to handle at root location. This is to display web page.
  server.on("/setPOS",mainserver); //--> Sets servo position from Web request
  server.begin();  
  Serial.println("HTTP server started");
}

void loop() {
  Rotary.Process( millis() );
  server.handleClient();
}
