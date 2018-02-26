/*
 * Credits to Marnick Hartgers
 * https://github.com/marnick-hartgers/ESD_HAN/blob/master/Lib_HAN/Lib_SimpleLED.ino
 */
struct SimpleLedLayout {
  int numSimpleLEDs;
  int simpleLEDsStartPort;
};

SimpleLedLayout simpleLedLayout = { 8, 6 };


void initSimpleLeds() {
  for (int i = simpleLedLayout.simpleLEDsStartPort; i < simpleLedLayout.simpleLEDsStartPort + simpleLedLayout.numSimpleLEDs; i++) {
    pinMode(i, OUTPUT);
  }
}
void initSimpleLeds(int numLeds, int startPort) {
  simpleLedLayout.numSimpleLEDs = numLeds;
  simpleLedLayout.simpleLEDsStartPort = startPort;
}

void setSimpleLed(int led, boolean on) {
  digitalWrite(simpleLedLayout.simpleLEDsStartPort + led, on ? HIGH : LOW);
}
void clearAllSimpleLeds() {
  for (int i = 0; i < simpleLedLayout.numSimpleLEDs; i++) {
    setSimpleLed(i, false);
  }
}
void setAllSimpleLeds(boolean on) {
  for (int i = 0; i < simpleLedLayout.numSimpleLEDs; i++) {
    setSimpleLed(i, on);
  }
}
void setPatternOnSimpleLeds(boolean pattern[]) {
  for (int i = 0; i < simpleLedLayout.numSimpleLEDs; i++) {
    setSimpleLed(i, pattern[i]);
  }
}

