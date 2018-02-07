int activeLed = 0;

void setup() {
  initSimpleLeds();
  
  setTimer(0,500, setLeds);
}

void loop() {
  updateTimers();
}

void setLeds(){
  //Serial.println("Loop: ");
  //Serial.print(activeLed);
  clearAllSimpleLeds();
  setSimpleLed(activeLed, true);
  activeLed++;
  if(activeLed >= 8){
    activeLed = 0;
  }
}

