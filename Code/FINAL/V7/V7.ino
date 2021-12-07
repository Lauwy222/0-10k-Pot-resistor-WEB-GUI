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
  }
}

//KY040 RIGHT
void OnButtonRight(void) {
  if(number!=100){
    ++number;

    displayrendering();    
  }}

//Server handling
void mainserver(){
  String POS = server.arg("VOLM");
  number = POS.toInt();
  delay(15);
  
  displayrendering();
  server.send(200, "text/plane","");
}

void returnpos() {
  String s = String(number, DEC);
  server.send(200, "text/plain", s); //Send web page
}

  //DISPLAY render
void displayrendering(){
  //SETPOT
  pot.setPot(number,true);
  //Calculate and transform
  volume = String(number, DEC);
  vol = "Volume: " + volume;
  //Serial MON
  Serial.println("Volume " + volume);
  Serial.println("Vol " + vol);
  //Display
  display.init();
  //AP&VOL
  String ipstat = WiFi.softAPIP().toString();
  String usr = String(ssid);
  String passw = String(password);
  display.drawString(0, 0, vol);
  display.drawString(0, 30, "IP: "+ipstat);
  display.drawString(0, 40, "SSID: "+usr);
  display.drawString(0, 50, "PASSW: "+passw);
  display.display();
  //Webserver update
//    POS = number;
  
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

  //Start AP
  WiFi.softAP(ssid, password); 

  IPAddress apip = WiFi.softAPIP(); 
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(password);
  Serial.print("IP: ");
  Serial.println(apip); 
 
  server.on("/",handleRoot);  
  server.on("/setPOS",mainserver);
  server.on("/getPOS",returnpos); 
  server.begin();  
  Serial.println("HTTP server started");

  displayrendering();
}

void loop() {
  Rotary.Process( millis() );
  server.handleClient();
}
