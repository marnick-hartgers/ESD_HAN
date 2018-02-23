# Librarys documentatie
## FIRST!
Ben dyslectisch as fuck

## Algemene instalatie van een lib. 
Download de file of clone de repo.
Sleep het bestand in de sketch folder van je arduino project.
DONE!

## Timers lib
###setTimer
Definitie:
````C
setTimer(int timerIndex, int interval, void(*callback)(void));
````
Met deze functie kun je een timer zetten. 
De timer zou de functie die je mee geeft aan de functie aanroepen iedere ingestelde periode.
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
  maintainTimers();//Houd de timers up te date. Deze moet je aanroepen wil je dat de lib werkt.
}

void timerCallback(){
    //Do things every 500ms
}
````
In de Lib_Timers.ino file vind de deze regel
````C
#define NUM_COUNTERS 10
````
Deze regel defineert 10 timer. Heb je meer dan 10 timers nodig dan moet je deze regel aanpassen naar een hoger getal.