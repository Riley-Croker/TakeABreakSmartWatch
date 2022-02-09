// Button Functions

void initButtons(){
  for (int i = 0; i < 4; i++) {
    buttons[i].attach(buttonPins[i], INPUT);
    buttons[i].interval(25);
  }
}

void updateButtons() {
  switch(mode) {
    case -1:
      if(timerIsDone) {
        buttons[0].update();
        if (buttons[0].rose()){
          timerIsDone = false;
          mode=-1;
          strip.clear();
        }
      }
      else {
        for (int i = 1; i < 4; i++)  {
          buttons[i].update();
          if (buttons[i].rose()){
            mode = i;
          }
        } 
      } 
    break;
    case 0:
    
    break;
    case 1:
      buttons[0].update();
      if(buttons[0].rose()) {
        resetStop();
      }
      buttons[1].update();
      if(buttons[1].rose()) {
        pauseStop();
      }
    
    break;
    case 2:
      buttons[0].update();
      if(buttons[0].rose()) {
        addHour++;
        if(addHour == 24)
          addHour=0;
      }
      buttons[1].update();
      if(buttons[1].rose()) {
        addMin++;
        if(addMin == 60)
          addMin=0;
      }
    break;
    case 3:
      buttons[0].update();
      if(buttons[0].rose()) {
        resetTimer();
      }
    break;
  }
}
