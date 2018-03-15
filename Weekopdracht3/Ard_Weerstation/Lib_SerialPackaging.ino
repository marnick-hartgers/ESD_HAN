#define startByte B10101010
#define sendBufferSize 512

#define dataTypeByte 0x0
#define dataTypeInt 0x1
#define dataTypeChar 0x2
#define dataTypeString 0x3


byte sendBuffer[sendBufferSize];
int writeIndex = 0;

void serialSendInt(byte key, int value) {
  byte data[] = {startByte, 0x0, 0x2, key, dataTypeInt, value >> 8, value};
  writeBuffer(data, 7);
}

void serialSendByte(byte key, byte value) {
  byte data[] = {startByte, 0x0, 0x1, key, dataTypeByte, value};
  writeBuffer(data, 6);
}

void serialSendChar(byte key, unsigned char value) {
  byte data[] = {startByte, 0x0, 0x1, key, dataTypeChar, value};
  writeBuffer(data, 7);
}

void serialSendString(byte key, String value) {
  unsigned int datalength = value.length();
  unsigned int totalLength = 7 + value.length();
  byte data [totalLength] = {startByte, totalLength >> 8, totalLength, key, dataTypeString,datalength >> 8, datalength};
  for (int i = 0; i < value.length(); i++) {
    data[i + 7] = value[i];
  }
  writeBuffer(data, totalLength);
}

byte generateCheckSum(){
  byte b = 0x0;
}

void writeBuffer(byte data[], int length) {
  //Calculate the end index for the write operation and check if it will fit in the buffer
  int endIndex =  writeIndex + length;
  if (endIndex >= sendBufferSize) {
    //Data does not fit, first send it before we write
    flushSendBuffer();
    //recalculate the end index
    endIndex =  writeIndex + length;
  }
  for (int i = 0; i < length; i++) {
    sendBuffer[writeIndex + i] = data[i];
  }
  writeIndex = endIndex;
  flushSendBuffer();
}

void flushSendBuffer() {
  Serial.write(sendBuffer, writeIndex);
  writeIndex = 0;
}


/* Package layout example
   byte | description
   0 | Start byte
   1 | package length
   2 | package length
   //Data begin
   3 | Value index
   5 | Value type
   6+| Value package
*/

/* String Format
   byte | desc
   0 | string length
   1 | string length
   2+| char's
*/
