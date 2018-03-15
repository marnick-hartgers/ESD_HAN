#define STATE_NONE 0
#define STATE_BOUND_MIN 1
#define STATE_BOUND_MAX 2
#define STATE_SPEED 3

#define TIMERHANDLE_SETTINGSUPDATE  1

int settingState = STATE_NONE;

void setup() {
  serialBegin(exeSerialCommand);
  initServo();
  saveBound(false, 0);
  saveBound(true, 180);
  saveSpeed(5);
  wipe();
  setTimer(TIMERHANDLE_SETTINGSUPDATE, 10, updateSettings);
}

void loop() {
  maintainTimers();
  maintainSerial();
}

void updateSettings() {
  switch (settingState) {
    case STATE_SPEED:
      setMaxValuePotentioMeter(30);
      saveSpeed(getPotentioMeterValue());
      break;
    case STATE_BOUND_MIN:
      setMaxValuePotentioMeter(180);
      saveBound(false, getPotentioMeterValue());
      break;
    case STATE_BOUND_MAX:
      setMaxValuePotentioMeter(180);
      saveBound(true, getPotentioMeterValue());
      break;
  }
}

void exeSerialCommand(byte cmd) {
  switch (cmd) {
    case '0':
      settingState = STATE_BOUND_MIN;
      break;
    case '1':
      settingState = STATE_BOUND_MAX;
      break;
    case 's':
      settingState = STATE_SPEED;
      break;
    case 'x':
      toggleWiper();
      break;
  }
}

