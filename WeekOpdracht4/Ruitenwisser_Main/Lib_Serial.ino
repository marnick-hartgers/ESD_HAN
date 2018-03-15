struct SerialConfig {
  int baudRate = 9200;
  void (*callback)(byte);
};

SerialConfig serialConfig;

void serialBegin(void (*callback)(byte)){
  Serial.begin(serialConfig.baudRate);
  serialConfig.callback = callback;
}

void maintainSerial(){
  int av = Serial.available();
  if(av > 0){
    byte buff[av];
    Serial.readBytes(buff, av);
    for(int i=0; i< av;i++){
      serialConfig.callback(buff[i]);
      Serial.println(buff[i], DEC);
    }
    
  }
}

