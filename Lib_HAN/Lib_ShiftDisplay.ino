/*
 * Credits to Marnick Hartgers
 * https://github.com/marnick-hartgers/ESD_HAN/blob/master/Lib_HAN/Lib_ShiftDisplay.ino
 */
byte currentDisplayData[2] = {0, 0};
//Init's the ports used to control the display
void initShiftLed(int data, int clock, int master) {
  pinMode(master, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);
}

void setDisplayHex(byte segchar) {
  currentDisplayData[0] = getByteFromNumber16(segchar / 16);
  currentDisplayData[1] = getByteFromNumber16(segchar % 16);
  setDisplayFromData();
}

void setDisplayFromData() {
  digitalWrite(masterPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST,  currentDisplayData[0]);
  shiftOut(dataPin, clockPin, MSBFIRST, currentDisplayData[1]);
  digitalWrite(masterPin, HIGH);
}

void setDisplayDot(boolean first, boolean on) {
  if (first) {
    if (on) {
      bitSet(currentDisplayData[0], 7);
    } else {
      bitClear(currentDisplayData[0], 7);
    }
  } else {
    if (on) {
      bitSet(currentDisplayData[1], 7);
    } else {
      bitClear(currentDisplayData[1], 7);
    }
  }
}

byte getByteFromNumber16(byte data) {
  byte d = 0;

  switch (data) {
    case 0:
      bitSet(d, 0);
      bitSet(d, 2);
      bitSet(d, 3);
      bitSet(d, 4);
      bitSet(d, 5);
      bitSet(d, 6);
      break;
    case 1:
      bitSet(d, 3);
      bitSet(d, 6);
      break;
    case 2:
      bitSet(d, 2);
      bitSet(d, 3);
      bitSet(d, 1);
      bitSet(d, 4);
      bitSet(d, 5);
      break;
    case 3:
      bitSet(d, 2);
      bitSet(d, 1);
      bitSet(d, 5);
      bitSet(d, 3);
      bitSet(d, 6);
      break;
    case 4:
      bitSet(d, 0);
      bitSet(d, 1);
      bitSet(d, 3);
      bitSet(d, 6);
      break;
    case 5:
      bitSet(d, 2);
      bitSet(d, 0);
      bitSet(d, 1);
      bitSet(d, 6);
      bitSet(d, 5);
      break;
    case 6:
      bitSet(d, 2);
      bitSet(d, 0);
      bitSet(d, 1);
      bitSet(d, 4);
      bitSet(d, 6);
      bitSet(d, 5);
      break;
    case 7:
      bitSet(d, 2);
      bitSet(d, 3);
      bitSet(d, 6);
      break;
    case 8:
      bitSet(d, 0);
      bitSet(d, 1);
      bitSet(d, 2);
      bitSet(d, 3);
      bitSet(d, 4);
      bitSet(d, 5);
      bitSet(d, 6);
      break;
    case 9:
      bitSet(d, 0);
      bitSet(d, 2);
      bitSet(d, 3);
      bitSet(d, 1);
      bitSet(d, 6);
      bitSet(d, 5);
      break;
    case 10:
      bitSet(d, 0);
      bitSet(d, 1);
      bitSet(d, 2);
      bitSet(d, 3);
      bitSet(d, 4);
      bitSet(d, 6);
      break;
    case 11:
      bitSet(d, 0);
      bitSet(d, 1);
      bitSet(d, 4);
      bitSet(d, 5);
      bitSet(d, 6);
      break;
    case 12:
      bitSet(d, 2);
      bitSet(d, 0);
      bitSet(d, 4);
      bitSet(d, 5);
      break;
    case 13:
      bitSet(d, 3);
      bitSet(d, 1);
      bitSet(d, 4);
      bitSet(d, 5);
      bitSet(d, 6);
      break;
    case 14:
      bitSet(d, 2);
      bitSet(d, 0);
      bitSet(d, 1);
      bitSet(d, 4);
      bitSet(d, 5);
      break;
    case 15:
      bitSet(d, 2);
      bitSet(d, 0);
      bitSet(d, 1);
      bitSet(d, 4);
      break;
  }
  return d;
}

