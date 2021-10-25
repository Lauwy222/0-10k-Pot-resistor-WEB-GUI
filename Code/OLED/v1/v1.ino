#include <Wire.h>  
#include "SSD1306.h"

SSD1306  display(0x3C, D2, D5); //Address set here 0x3C that I found in the scanner, and pins defined as D2 (SDA/Serial Data), and D5 (SCK/Serial Clock).

void setup()   {                
  display.init();
  display.flipScreenVertically();
  display.drawString(0, 0, "Hello world");
  display.display();
}

void loop() {
}
