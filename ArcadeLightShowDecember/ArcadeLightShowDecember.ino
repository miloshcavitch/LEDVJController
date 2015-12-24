#include <Bounce2.h>
#include "LightShowLibrary.h"
#include <stdio.h>
#define DIRCOUNT 4
#define BUTTONCOUNT 8

const int DIRECTION[] = {47, 49, 51, 53};// order is left, up, right down. Orange wire on arcade stick is ground.
const int dCount = DIRCOUNT;
const int btnCount = BUTTONCOUNT;
const int buttonPins[BUTTONCOUNT] = {52, 50, 48, 46, A0, A1, A2, A3};
int dState[4];
int prvDState[4];

int bState[8];
int prvBState[8];
bool leftrightMode;
bool strobeMode;
bool LFOMode;
bool strobe;
unsigned long strobetime = 50000;
unsigned long lastStrobeEvent;


unsigned long mictime = 0;
unsigned long lastMicEvent = 0;
unsigned long loopTime = 0;
unsigned long intervalTime = 5000;
int i = 0;

int colorPalette[BUTTONCOUNT][3] = {
  {255, 0, 0},//red
  {125, 0, 120},//purple
  {50, 0, 190},//purple
  {0, 0, 225},//blue------------
  {110, 135, 0},//yellow
  {0, 225, 0},//green
  {0, 180, 70},//turqoise
  {0, 90, 140}//turqoise
};
int colorOffset = 0;

int bOVal[8] = {
  95, 191, 286, 382, 477, 573, 669, 0
};

const int kRed = 2;
const int kGreen = 3;
const int kBlue = 4;
const int kStrobe = 5;

LightShowController lsc;
colorWheel rightMode;
  
int red, green, blue;



Bounce directionDebouncer[4];
Bounce buttonDebouncer[8];

int sum_array(int a[], int num_elements)
{
   int i, sum=0;
   for (i=0; i<num_elements; i++)
   {
   sum = sum + a[i];
   }
   return(sum);
}

void setup(){
  Serial.begin(115200);
  pinMode(kRed, OUTPUT);
  pinMode(kGreen, OUTPUT);
  pinMode(kBlue, OUTPUT);
  pinMode(kStrobe, OUTPUT);
  
  for(int i = 0; i <btnCount; i++){
    pinMode(buttonPins[i], INPUT);
    digitalWrite(buttonPins[i], HIGH);
    buttonDebouncer[i].attach(buttonPins[i]);
    buttonDebouncer[i].interval(5);
  }
  for(int i = 0; i < dCount; i++){
    pinMode(DIRECTION[i], INPUT);
    digitalWrite(DIRECTION[i], HIGH);
    directionDebouncer[i].attach(DIRECTION[i]);
    directionDebouncer[i].interval(5);
  }
  rightMode.test(lsc);
}
void loop(){
  mictime = micros();
  for (int i = 0; i < dCount; i++){
    directionDebouncer[i].update();
    prvDState[i] = dState[i];
    dState[i] = directionDebouncer[i].read(); 
  }
  if (prvDState[0] != dState[0] && dState[0] == 0){
    leftrightMode = LOW;
  }
  if (prvDState[2] != dState[2] && dState[2] == 0){
    leftrightMode = HIGH;
  }
  
  for (int i = 0; i < btnCount; i++){
    buttonDebouncer[i].update();
    bState[i] = buttonDebouncer[i].read();
    if (bState[i] == LOW){//inverse logic
      colorOffset = bOVal[i];
    }
  }
  if(mictime >= (lastMicEvent + intervalTime)){
  rightMode.standardMarch(red, green, blue, i, lsc, colorOffset);
  lastMicEvent = mictime;
  }
  if (mictime >= (lastStrobeEvent + strobetime)){
    strobe = !strobe;
    lastStrobeEvent = mictime;
  }

  if (strobe){
    analogWrite(kRed, 255);
    analogWrite(kGreen, 255);
    analogWrite(kBlue, 255);    
  }else{
    analogWrite(kRed, 255 - red);
    analogWrite(kGreen, 255 -green);
    analogWrite(kBlue, 255 - blue);
  }
  /*Serial.println(red);
  Serial.print(" ");
  
  Serial.print(green);
  Serial.print(" ");
  
  Serial.print(blue);
  Serial.print(" ");
*/
}
