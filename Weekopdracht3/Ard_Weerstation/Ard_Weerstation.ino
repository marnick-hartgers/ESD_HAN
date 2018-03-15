

void setup() {
  Serial.begin(9600);
  startTempSensor();
  setTimer(0,1000, sendUpdate);

}

void loop() {
  maintainTimers();

}

void sendUpdate(){
  if (isTempSensorReady()) {
    startGetTemp();
  }
  serialSendInt(0x0, getWindDirection());
  serialSendInt(0x2, getLightInLux());
  serialSendInt(0x1, getLastTempReading());
}

