#include "Arduino.h"
#include "LightShowLibrary.h"
#include <math.h>
LightShowController::LightShowController(){
  //set array of color spectrum going from red to green to blue to red again, in 8 bit RGB values.
    int rSet = 255;
    int gSet = 0;
    int bSet = 0;
    
  for (int i = 0; i < 255; i++)
  {
    ColorWheel[i][0] = rSet;
    ColorWheel[i][1] = gSet;
    ColorWheel[i][2] = bSet;
    rSet--;
    gSet++;
  }
  for (int i = 255; i < 510; i++)
  {
    ColorWheel[i][0] = rSet;
    ColorWheel[i][1] = gSet;
    ColorWheel[i][2] = bSet;
    gSet--;
    bSet++;
  }
  for (int i = 510; i < 765; i++)
  {
    ColorWheel[i][0] = rSet;
    ColorWheel[i][1] = gSet;
    ColorWheel[i][2] = bSet;
    rSet++;
    bSet--;
  }
  //below variables are temporary until i figure out how to work with ableton
}


void colorWheel::standardMarch(int &r, int &g, int &b, int &i, LightShowController &ls, int offset){
  i++;
  int j = i + offset;
  if (j > 765){
    j = j - 765;
  }
  r = ls.ColorWheel[j][0];
  g = ls.ColorWheel[j][1];
  b = ls.ColorWheel[j][2];
  if(i >= 765){
    i = 0;
  }
}

void colorWheel::test(LightShowController &ls){
  for (int j = 0; j < 765; j++){
    Serial.println("red ");
    Serial.print(ls.ColorWheel[j][0]);
    Serial.print("green ");
    Serial.print(ls.ColorWheel[j][1]);
    Serial.print("blue ");
    Serial.print(ls.ColorWheel[j][2]);
  }
}

