// States
#include "tinysnore.h"  // Include TinySnore Library
int mode = -1;          // -1: Sleep || 0 - Red || 1 - Green || 2 - Blue || 3 - Pink

// NeoPixels
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip(12, 0, NEO_GRB + NEO_KHZ800);

// Buttons
#include <Bounce2.h>
int buttonPins[4] = {1, 2, 3, 4};
Bounce * buttons = new Bounce[4];

// Time
int curHours = 0;
int curMinutes = 0;
int curSeconds = 0;
unsigned long addMin = 0;
unsigned long addHour = 0;
int minBin[6] = {0,0,0,0,0,0};
int hourBin[6] = {0,0,0,0,0,0};

//Timer
boolean timerIsGoing = false;
int snoozeNum = 0;
boolean timerIsDone = false;

//StopWatch
int curMinutesS = 0;
int curSecondsS = 0;
int minBinS[6] = {0,0,0,0,0,0};
int secBinS[6] = {0,0,0,0,0,0};
boolean stopIsGoing = false;
int snoozeNumSW = 0;

void setup() {
  initButtons();
  initNeopixels();
}    
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
void loop() {
  updateButtons();
  updateTime();
  updateBinLists();
  if(timerIsGoing) updateTimer();
  if(stopIsGoing) {updateStop(); updateBinListsStop(); }
  
  
  switch(mode){
    case -1: 
      if(!timerIsDone)
        fallAsleep(); 
      else
        rgb();
    break;
    case 0: allNeopixels(0); break;
    case 1: showStop(); break;
    case 2: tellTime(); break;
    case 3: showTimer(); break;
  }

}
