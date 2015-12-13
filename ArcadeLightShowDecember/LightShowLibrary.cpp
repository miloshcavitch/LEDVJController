#include "Arduino.h"
#include "LightShowLibrary.h"

LightShowController::LightShowController(int serialInfo, int knobInfo){
  int rSet = 255;
  int grSet = 0;
  int bSet = 0;
  int rD = -1;
  int grD = 1;
  int bD = 0;
  //set array of color spectrum going from red to green to blue to red again, in 8 bit RGB values.
  for (int i = 0; i < 765; i++)
  {
    ColorWheel[i][0] = rSet;
    ColorWheel[i][1] = grSet;
    ColorWheel[i][2] = bSet;
    if (rSet >= 255){
      rD = -1;
      grD = 1;
      bD = 0;
    }
    if (grSet >= 255){
      rD = 0;
      grD = -1;
      bD = 0;
    }
    if (bSet >= 255){
      rD = 1;
      grD = 0;
      bD = -1;
    }
    rSet += rD;
    grSet += grD;
    bSet += bD;
  }
  //below variables are temporary until i figure out how to work with ableton

  updateBPM(serialInfo);
  setFractionTime(knobInfo);
}
