// NeoPixel Functions

void initNeopixels(){
  strip.begin();
  strip.clear();
  strip.show();
  strip.setBrightness(15);
}

void allNeopixels(int c){
  for (int i = 0; i < strip.numPixels(); i++){
    strip.setPixelColor(i, Wheel(c));
  }
  strip.show();
  mode = -1;
}

void tellTime() {
  uint32_t tempC;
  int minPlaceHolder = 11;
  int hourPlaceHolder = 5;
  for(int i = 0; i < 6; i++) {
    if(minBin[i] == 1) tempC = Wheel(0);
    else tempC = Wheel(128);
    strip.setPixelColor(minPlaceHolder, tempC);
    if(hourBin[i] == 1) tempC = Wheel(0);
    else tempC = Wheel(128);
    strip.setPixelColor(hourPlaceHolder, tempC);

    minPlaceHolder--;
    hourPlaceHolder--;
  }
  strip.show();
  fallAsleep();
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void rgb() {
  strip.clear();
  for(int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel(map(i,0,strip.numPixels(),0,255)));
  }
  strip.show();
}
