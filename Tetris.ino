#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "header.h"

void setup() {
  display.begin(0x3C);
  display.clearDisplay();
  step = sizeof(Position);
  speed = 2;
  
  for(int i = 0; i < Y_COUNT; i++){
    for(int j = 0; j < X_COUNT; j++){
      fallen_acc[i][j] = 0;
    }
  }
  
  UpdateFigure();
}

void loop() {
  checkButtons();

  if(millis() - timer >= 1000 / speed){
    timer = millis();
    display.clearDisplay();
    Fall();
    Redraw();
    display.display();
  }
}
