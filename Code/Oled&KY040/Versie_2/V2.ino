#include "KY040rotary.h"
#include <Wire.h>  
#include "SSD1306.h"

// init the button
KY040 Rotary(D5, D6, D7);
SSD1306  display(0x3C, D2, D3);


void OnButtonClicked(void) {
  Serial.println("Button 1: clicked");
  display.init();
  display.drawString(0, 0, "Button 1: clicked");
  display.display();
}
void OnButtonLeft(void) {
  Serial.println("Button 1: rotating left");
  display.init();
  display.drawString(0, 0, "Button 1: rotating left");
  display.display();
}
void OnButtonRight(void) {
  Serial.println("Button 1: rotating right");
  display.init();
  display.drawString(0, 0, "Button 1: rotating right");
  display.display();
}


void setup() {
  // open the serial port
  display.init();
  Serial.begin(115200);
  Serial.println("Starting...");
  display.drawString(0, 0, "Starting...");
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
