#define NUM_BUTTONS 10

struct ButtonSetting{
  int port = -1;
  void (*callback)(void);
  boolean state;
};

ButtonSetting buttonSettings[NUM_BUTTONS];

void setButtonCallBack(int buttonIndex, int buttonPort, void(*callback)(void)){
  buttonSettings[buttonIndex].port = buttonPort;
  buttonSettings[buttonIndex].callback = callback;
  pinMode(buttonPort, INPUT_PULLUP);
}

void maintainButtons(){
  for(int i=0; i < NUM_BUTTONS; i++){
    if(buttonSettings[i].port != -1){
      boolean state = digitalRead(buttonSettings[i].port) == HIGH;
      if(buttonSettings[i].state != state){
        buttonSettings[i].state = state;
        if(!state){
          buttonSettings[i].callback();
        }
      }
    }
  }
}

