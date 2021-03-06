struct SerialConfig {
  int bautRate = 19200;
  boolean serialInitialised = false;
  void(*dataCallback)(String data);
};

SerialConfig serialConfig;

void startSerial( void(*callback)(String data)) {
  Serial.begin(serialConfig.bautRate);
  serialConfig.serialInitialised = true;
  serialConfig.dataCallback = callback;
}

void maintainSerial() {
  if (Serial.available() > 0) {
    String data = Serial.readString();
    serialConfig.dataCallback(data);
  }
}
