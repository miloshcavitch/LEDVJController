#include "Arduino.h"

class LightShowController
{
private:
  colorWheel* CWO;

public:
  int ColorWheel[765][3];
  int Tempo;
  unsigned long TempoinMicros;
  float fractionTime;

  //updates Tempo and TempoinMicros
  void updateBPM(int serialInfo);

  //set whether events happen on quarter notes, 1/16th etc.
  void setfractionTime(int knobInfo);
  //points to colorWheel object to
  void connectColorWheel(colorWheel* CWObject);
  void connectColorPulse(colorPulse* CPObject);
};

class colorWheel
{
private:
  bool justFlipped;
  bool active;
public:

}
