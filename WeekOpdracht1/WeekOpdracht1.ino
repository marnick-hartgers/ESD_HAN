#define speedStep 10

struct LedConfig {
  int stepSpeed = 500;
  int currentStep = 0;
  int mode = 0;
};

LedConfig ledConfig;

void setup() {
  initSimpleLeds();
  startSerial(onSerialMessage);
  setTimer(0, 500, setLeds);
}

void loop() {
  maintainSerial();
  maintainTimers();
}

void setLeds() {
  clearAllSimpleLeds();
  switch (ledConfig.mode) {
    case 0:
      setLedMode0();
      break;
    case 1:
      setLedMode1();
      break;
    case 2:
      setLedMode2();
      break;

  }
}

void setLedMode0() {
  if (ledConfig.currentStep >= getPattern1Length()) {
    ledConfig.currentStep = 0;
  }
  setPatternOnSimpleLeds(getPattern1(ledConfig.currentStep));
  ledConfig.currentStep++;
}

void setLedMode1() {
  if (ledConfig.currentStep >= getPattern2Length()) {
    ledConfig.currentStep = 0;
  }
  setPatternOnSimpleLeds(getPattern2(ledConfig.currentStep));
  ledConfig.currentStep++;
}

void setLedMode2() {
  if (ledConfig.currentStep >= getPattern3Length()) {
    ledConfig.currentStep = 0;
  }
  setPatternOnSimpleLeds(getPattern3(ledConfig.currentStep));
  ledConfig.currentStep++;
}

void setMode(int mode) {
  ledConfig.mode = mode;
  ledConfig.currentStep = 0;
}

void setStepSpeed(int stepSpeed) {
  ledConfig.stepSpeed = stepSpeed;
  intervalTimer(0, ledConfig.stepSpeed);
}

void increaseSpeed() {
  setStepSpeed(ledConfig.stepSpeed + speedStep);
}

void decreaseSpeed() {
  if (ledConfig.stepSpeed > speedStep) {
    setStepSpeed(ledConfig.stepSpeed - speedStep);
  }
}

void onSerialMessage(String data) {
  for (char d : data) {
    switch (d) {
      case 'e':
        setMode(-1);
        break;
      case 'h':
        setMode(0);
        break;
      case 's':
        setMode(1);
        break;
      case 'p':
        setMode(2);
        break;
      case '-':
        decreaseSpeed();
        break;
      case '+':
        increaseSpeed();
        break;
    }
  }
}

