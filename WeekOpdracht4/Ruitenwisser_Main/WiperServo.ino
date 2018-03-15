#define ARRD_BOUNDMIN  0x0
#define ARRD_BOUNDMAX  0x1
#define ARRD_SPEED  0x2

#define TIMERHANDLE_SERVO 0

#include <EEPROM.h>
#include <Servo.h>

struct WiperConfig {
  //Saved Values
  byte boundMin = 0;
  byte boundMax = 180;
  byte speed = 10;


  byte port = 3;
  boolean retracted = false;
  boolean busy = false;
  boolean wipe = false;
  int currentAngle = 0;

  void restore() {
    //I dont want to waste the EEPROM
    //boundMin = EEPROM.read(ARRD_BOUNDMIN);
    //boundMax = EEPROM.read(ARRD_BOUNDMAX);
    //speed = EEPROM.read(ARRD_SPEED);
  }

  void save() {
    //I dont want to waste the EEPROM
    //EEPROM.write(ARRD_BOUNDMIN, boundMin);
    //EEPROM.write(ARRD_BOUNDMAX, boundMax);
    //EEPROM.write(ARRD_SPEED, speed);
  }

};

WiperConfig wiperConfig;
Servo servo;

void initServo() {
  wiperConfig.restore();
  servo.attach(wiperConfig.port);
  servo.write(wiperConfig.boundMin);
  setTimer(TIMERHANDLE_SERVO, 50, updateServo);
}

void wipe() {
  wiperConfig.busy = true;
  wiperConfig.wipe = true;
}

void stopWiping() {
  wiperConfig.wipe = false;
}

void toggleWiper() {
  if (wiperConfig.wipe) {
    stopWiping();
  } else {
    wipe();
  }
}

void saveBound(boolean minOrMax, int value) {
  if (minOrMax) {
    if (value > wiperConfig.boundMin &&  value != wiperConfig.boundMax) {
      wiperConfig.boundMax = value;
      wiperConfig.save();
    }
  } else {
    if (value < wiperConfig.boundMax &&  value != wiperConfig.boundMin) {
      wiperConfig.boundMin = value;
      wiperConfig.save();
    }
  }
}

void saveSpeed(byte value) {
  if (wiperConfig.speed != value) {
    wiperConfig.speed = value;
    wiperConfig.save();
  }
}

//Private section
void updateServo() {
  if (wiperConfig.busy) {
    if (!wiperConfig.retracted) {
      wiperConfig.currentAngle += wiperConfig.speed;
      if (wiperConfig.currentAngle > wiperConfig.boundMax) {
        wiperConfig.currentAngle = wiperConfig.boundMax;
        wiperConfig.retracted = true;
      }
    } else {
      wiperConfig.currentAngle -= wiperConfig.speed;
      if (wiperConfig.currentAngle < wiperConfig.boundMin) {
        wiperConfig.currentAngle = wiperConfig.boundMin;
        wiperConfig.retracted = false;
        wiperConfig.busy = wiperConfig.wipe;
      }
    }
    servo.write(wiperConfig.currentAngle);
  }
}

