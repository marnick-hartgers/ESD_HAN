int buzzerPort;

void initBeep(int port){
  buzzerPort = port;
  pinMode(port, OUTPUT);
}

void beep(int hz, int time){
  tone(buzzerPort, hz, time);
}

