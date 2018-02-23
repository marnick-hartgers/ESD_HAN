int diceMax = 6;
int diceSpeed = 25;
int diceValue = 0;
boolean diceRunning = false;
int diceRunOutStep = 0;
int diceRunOutTrigger = 0;
int diceRunOutStepCounter = -1;
int diceRunOutMaxSteps = -1;

void setDiceBounds(int dMax) {
  diceMax = dMax;
}

void setDiceSpeedInHz(int dSpeed) {
  diceSpeed = dSpeed;
  calculateDiceSpeed();
}

void calculateDiceSpeed() {
  setTimer(0, 1000 / diceSpeed, diceLoop);
}

void startDice() {
  diceRunOutMaxSteps = -1;
  diceRunOutStepCounter = 0;
  diceRunOutTrigger = 0;
  calculateDiceSpeed();
  diceRunning = true;
}

void stopDice() {
  diceRunning = false;
}

void runOutDice(int runOutTime) {
  diceRunOutMaxSteps = runOutTime / (1000 / diceSpeed);
  diceRunOutTrigger = 0;
}

void diceLoop() {
  //Check if the dice is rolling
  if (diceRunning) {
    //Check if the dice is rolling out
    if (diceRunOutMaxSteps > -1) {
      //This will lower the dice speed everytime it raises the number
      if (diceRunOutStep >= diceRunOutTrigger) {
        diceRunOutTrigger++;
        diceRunOutStep = 0;
        higherDice();
      }
      //This limits the amount of times that the dice is running when the dice is rolling out
      diceRunOutStep++;
      if (diceRunOutStepCounter >= diceRunOutMaxSteps) {
        stopDice();
      }
      diceRunOutStepCounter++;
    } else {
      //Just roll the dice
      higherDice();
    }
  }
}

void higherDice() {
  diceValue++;
  if (diceValue > diceMax) {
    diceValue = 0;
  }
  beep(440, 10);
}

int getDiceValue() {
  return diceValue;
}
boolean isDiceRunning(){
  return diceRunning;
}

