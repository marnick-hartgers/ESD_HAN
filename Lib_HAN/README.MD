# Librarys documentatie
## FIRST!
Ben dyslectisch as fuck

## Algemene instalatie van een lib. 
Download de file of clone de repo.
Sleep het bestand in de sketch folder van je arduino project.
DONE!

## Timers lib
````C
setTimer(int timerIndex, int interval, void(*callback)(void));
````
Met deze functie kun je een timer zetten. 
De timer zou de functie die je mee geeft aan de functie gedurende interval aanroepen.
Parameters:
````C
int timerIndex = de id van de timer
int interval = interval in miliseconde
void(*callback)(void) naam van de functie die uitgevoert moet worden als de timer klaar is
```` 
Voorbeeld:
````C
void setup() {
  setTimer(0,500,timerCallback);
}

void loop() {
  maintainTimers();
}

void timerCallback(){
    //Do things every 500ms
}
````