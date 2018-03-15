#include <OneWire.h>

#define tempSensortPin 3

OneWire tempSensor(tempSensortPin);
byte tempSensorAddres[8];

#define STATE_SEARCHING 0
#define STATE_READY 1
#define STATE_READING 2
int sensorState = STATE_SEARCHING;

int lastReading = 0;

#define START_TIMER_HANDLE 1
#define READ_TIMER_HANDLE 2

void startTempSensor() {
  checkSensorState();
  setTimer(START_TIMER_HANDLE, 1000, checkSensorState);
}

void checkSensorState() {
  if (isTempSensorReady()) {
    clearTimer(START_TIMER_HANDLE);
  }
  if ( tempSensor.search(tempSensorAddres) && OneWire::crc8(tempSensorAddres, 7) == tempSensorAddres[7]) {
    clearTimer(START_TIMER_HANDLE);
    sensorState = STATE_READY;
  } else {
    tempSensor.reset_search();
  }
}

boolean isTempSensorReady() {
  return sensorState == STATE_READY;
}

void startGetTemp() {
  sensorState = STATE_READING;
  tempSensor.reset();
  tempSensor.select(tempSensorAddres);
  tempSensor.write(0x44);
  setTimer(READ_TIMER_HANDLE, 950, readTempSensor);
}

void readTempSensor() {
  clearTimer(READ_TIMER_HANDLE);
  byte sensorData[12];
  float celsius;
  tempSensor.reset();
  tempSensor.select(tempSensorAddres);
  tempSensor.write(0xBE);
  for (int i = 0; i < 9; i++) {
    sensorData[i] = tempSensor.read();
  }
  int16_t raw = (sensorData[1] << 8) | sensorData[0];
  byte cfg = (sensorData[4] & 0x60);
  if (cfg == 0x00) {
    raw = raw & ~7;
  } else if (cfg == 0x20) {
    raw = raw & ~3;
  } else if (cfg == 0x40) {
    raw = raw & ~1;
  }
  lastReading = (int)((float)raw / 16.0 * 100);
  sensorState = STATE_READY;
}

int getLastTempReading(){
  return lastReading;
}

