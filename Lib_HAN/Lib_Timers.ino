/*
 * Credits to Marnick Hartgers
 * https://github.com/marnick-hartgers/ESD_HAN/blob/master/Lib_HAN/Lib_Timers.ino
 */

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

void clearTimer(int timerPointer){
  timers[timerPointer].interval = -1;
}

void resetTimer(int timerPointer){
  timers[timerPointer].startTime = millis();
}

void intervalTimer(int timerPointer, int interval){
  if(timers[timerPointer].callback){
    timers[timerPointer].interval = interval;
  }  
}


void maintainTimers(){
  for(int t = 0; t < NUM_COUNTERS;t++){
    if(timers[t].interval != -1 && (timers[t].startTime + timers[t].interval) < millis()){
      timers[t].callback();
      timers[t].startTime = millis();
    }
  }
}

long getTimerInterval(int timerPointer) {
  return timers[timerPointer].interval;  
}


