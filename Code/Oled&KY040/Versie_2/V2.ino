#include "KY040rotary.h"
#include <Wire.h>  
#include "SSD1306.h"

// init the button
KY040 Rotary(D5, D6, D7);
//init the display
SSD1306  display(0x3C, D2, D3);
//set & calculate values
int number = 50;
String volume = String(number, DEC);
String vol = "Volume: " + volume;

void OnButtonClicked(void) {
  Serial.println("Button 1: clicked");
  display.init();
  display.drawString(0, 0, "Button 1: clicked");
  display.display();
}
void OnButtonLeft(void) {
 if(number!=0){
    --number;
    volume = String(number, DEC);
    vol = "Volume: " + volume;
    Serial.println("Volume " + volume);
    Serial.println("Vol " + vol);
    display.init();
    display.drawString(0, 0, vol);
    display.display();
    digitalWrite(16, LOW);
    digitalWrite(4, HIGH);
    delay(20);
    digitalWrite(4, LOW);
  }
}
void OnButtonRight(void) {
  if(number!=100){
    ++number;
    volume = String(number, DEC);
    vol = "Volume: " + volume;
    Serial.println("Volume " + volume);
    Serial.println("Vol " + vol);
    display.init();
    display.drawString(0, 0, vol);
    display.display();
    digitalWrite(16, HIGH);
    digitalWrite(4, HIGH);
    delay(100);
    digitalWrite(4, LOW);
  }
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
}


void loop() {
  Rotary.Process( millis() );
}
