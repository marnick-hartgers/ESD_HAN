struct PotentioConfig{
  int port = 0;
  int maxValue = 1023;
};

PotentioConfig potConfig;

void setMaxValuePotentioMeter(int val){
  potConfig.maxValue = val;
}

int getPotentioMeterValue(){
  return map(analogRead(potConfig.port), 0, 1023 , 0 , potConfig.maxValue);
}

