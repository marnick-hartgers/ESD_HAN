#define NUM_COUNTERS 10

struct TimerObject{
  long interval = -1;
  long startTime = 0;
  void (*callback)(void);
};

TimerObject timers [NUM_COUNTERS];

void setTimer(int timerPointer, int interval, void (*timerCallback)(void)){
  timers[timerPointer].interval = interval;
  timers[timerPointer].callback = timerCallback;
  timers[timerPointer].startTime = millis();
}

void updateTimers(){
  for(int t = 0; t < NUM_COUNTERS;t++){
    if(timers[t].interval != -1 && (timers[t].startTime + timers[t].interval) < millis()){
      timers[t].startTime = millis() + 10000;
      timers[t].callback();
      timers[t].startTime = millis();
    }
  }
}

