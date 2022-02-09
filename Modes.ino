// Modes

unsigned long sleepTimer = 0;
long sleepInterval = 10;
unsigned long sleepNumber = 0;

void fallAsleep(){
  if((millis()/1000) - sleepTimer > sleepInterval){
    strip.clear(); strip.show();  // Clear out NeoPixel Display
    snore(5000);                 // Go to Sleep for 5 Seconds
    sleepNumber++;
    snoozeNum++;
    if(stopIsGoing)
      snoozeNumSW++;   
    sleepTimer = millis() / 1000;
    mode = -1;
  }
}

// StopWatch Functions (mode 1)

unsigned long lastSeconds = 0;
unsigned long savedSeconds = 0;

void pauseStop() {
  if(!stopIsGoing)
    lastSeconds = (millis() / 1000) - savedSeconds;
  else
    savedSeconds = curSecondsS;
  stopIsGoing = !stopIsGoing;
}

void showStop() {
  uint32_t tempC;
  int secPlaceHolder = 11;
  int minPlaceHolder = 5;
  for(int i = 0; i < 6; i++) {
    if(secBinS[i] == 1) tempC = Wheel(0);
    else tempC = Wheel(128);
    strip.setPixelColor(secPlaceHolder, tempC);
    if(minBinS[i] == 1) tempC = Wheel(0);
    else tempC = Wheel(128);
    strip.setPixelColor(minPlaceHolder, tempC);

    secPlaceHolder--;
    minPlaceHolder--;
  }
  strip.show();
  fallAsleep();  
}

void updateBinListsStop() {
  if(curMinutesS == 0) {
    for(int i = 0; i < 6; i++) {
      minBinS[i] = 0;
    }
  }
  if(curSecondsS == 0) {
    for(int i = 0; i < 6; i++) {
      secBinS[i] = 0;
    }
  }
  int tempSec = curSecondsS;
  int secRotations = 0;
  int tempMin = curMinutesS;
  int minRotations = 0;
  while (tempSec > 0) {
    secBinS[secRotations] = tempSec % 2;
    tempSec = tempSec / 2;
    secRotations++;
  }
  while (tempMin > 0) {
    minBinS[minRotations] = tempMin % 2;
    tempMin = tempMin / 2;
    minRotations++;
  }
}

void updateStop() {
  curSecondsS = (millis() / 1000) - lastSeconds + (snoozeNumSW*5);
  if (curSecondsS >= 60) {
    softResetStop();
    curMinutesS++;
  }  
}

void softResetStop() {
  curSecondsS = 0;
  savedSeconds = 0;
  lastSeconds = millis() / 1000;
  for(int i = 0; i < 6; i++) {
    secBinS[i] = 0;
  }
  snoozeNumSW = 0;
}

void resetStop() {
  stopIsGoing = false;
  curSecondsS = 0;
  curMinutesS = 0;
  savedSeconds = 0;
  lastSeconds = millis() / 1000;
  for(int i = 0; i < 6; i++) {
    secBinS[i] = 0;
  }
  for(int i = 0; i < 6; i++) {
    minBinS[i] = 0;
  }
  snoozeNumSW = 0;
}

// Timer Functions (mode 3)

unsigned long startTime = 0;
long timerInterval = 12;
long pixelInterval = timerInterval / 12;
int showPixels = 12;


void updateTimer() {
  unsigned long curTime = (millis() / 1000)+(snoozeNum*5);
  unsigned long distance = curTime;
  showPixels=12;

  while(distance > (startTime + pixelInterval)) {
    showPixels--;
    distance-=pixelInterval;
  }
    
  if(curTime - startTime > timerInterval) {
    timerIsGoing = false;
    timerIsDone = true;
  }
}

void showTimer() {
  if(!timerIsGoing) {
    for(int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i,Wheel(0));
    }
  }
  else {
    for(int i = 0; i < showPixels; i++) {
      strip.setPixelColor(i,Wheel(128));
    }
    for(int i = showPixels; i < strip.numPixels(); i++) {
      strip.setPixelColor(i,Wheel(0));
    }
  }
  strip.show();
  fallAsleep();
}

void resetTimer() {
  timerIsGoing = true;
  startTime = millis() / 1000;
  showPixels = 12;
  snoozeNum = 0;
}




// Time Functions (mode 2)

void updateTime(){
  curMinutes=addMin;
  curHours=addHour;
  curSeconds = millis() / 1000;
  curSeconds += (sleepNumber*5);
  while (curSeconds >= 60) {
    curMinutes++;
    curSeconds-=60;
  }
  while (curMinutes >= 60) {
    curHours++;
    curMinutes-=60;
  }
  curHours = curHours % 24;
}

void updateBinLists() {
  if(curHours == 0) {
    for(int i = 0; i < 6; i++) {
      hourBin[i] = 0;
    }
  }
  if(curMinutes == 0) {
    for(int i = 0; i < 6; i++) {
      minBin[i] = 0;
    }
  }
  int tempMin = curMinutes;
  int minRotations = 0;
  int tempHours = curHours;
  int hourRotations = 0;
  while (tempMin > 0) {
    minBin[minRotations] = tempMin % 2;
    tempMin = tempMin / 2;
    minRotations++;
  }
  while (tempHours > 0) {
    hourBin[hourRotations] = tempHours % 2;
    tempHours = tempHours / 2;
    hourRotations++;
  }
}
