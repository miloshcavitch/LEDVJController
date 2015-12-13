#include "Arduino.h"

class LightShowController
{

public:
  int ColorWheel[765][3];
  int Tempo;
  unsigned long TempoinMicros;
  float fractionTime;

  //updates Tempo and TempoinMicros
  void updateBPM(int serialInfo);

  //set whether events happen on quarter notes, 1/16th etc.
  void setfractionTime(int knobInfo);
};

class colorWheel
{
private:
  bool justFlipped;
  bool active;
  LightShowController* eLeSCee;
public:
  void wheelStep(unsigned long elTime, int* r, int* g, int* b);
  void connectController(LightShowController* LSC);
}
