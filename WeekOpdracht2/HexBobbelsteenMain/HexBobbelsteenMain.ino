#define dataPin 10
#define masterPin 11
#define clockPin 12


void setup() {
  initBeep(13);
  initShiftLed(dataPin, clockPin, masterPin);
  startSerial(onSerialMessage);
  setDiceBounds(15);
  setDiceSpeedInHz(25);
  setButtonCallBack(0, 8, buttonPress);
}

void loop() {
  maintainSerial();
  maintainTimers();
  maintainButtons();
  setDisplayHex(getDiceValue());
  setDisplayDot(true, isDiceRunning());
}

void onSerialMessage(String data) {
  for (char command : data) {
    switch (command) {
      case 'S':
      case 's':
        startDice();
        break;
      case 'H':
      case 'h':
        runOutDice(5000);
        break;
    }
  }
}

void buttonPress() {
  if (isDiceRunning()) {
    runOutDice(5000);
  }else {
    startDice();
  }
}
