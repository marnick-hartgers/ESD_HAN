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

void setTimer(int timerIndex, long interval, void (*timerCallback)(void)){
  timers[timerIndex].interval = interval;
  timers[timerIndex].callback = timerCallback;
  timers[timerIndex].startTime = millis();
}

void clearTimer(int timerIndex){
  timers[timerIndex].interval = -1;
}

void resetTimer(int timerIndex){
  timers[timerIndex].startTime = millis();
}

void intervalTimer(int timerIndex, long interval){
  if(timers[timerIndex].callback){
    timers[timerIndex].interval = interval;
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

long getTimerInterval(int timerIndex){
  return timers[timerIndex].interval;
}