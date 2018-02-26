# Librarys documentatie
### FIRST!
Ben dyslectisch as fuck

### Algemene instalatie van een lib. 
Download de file of clone de repo.
Sleep het bestand in de sketch folder van je arduino project.
DONE!

## Timers lib
### setTimer
Definitie:
````C
setTimer(int timerIndex, long interval, void(*callback)(void))
````
Met deze functie kun je een timer zetten. 
De timer zou de functie die je mee geeft aan de functie aanroepen iedere ingestelde periode.
Parameters:
````C
int timerIndex = de id van de timer
long interval = interval in miliseconde
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

### clearTimer
Definitie:
````C
void clearTimer(int timerIndex)
````
Verwijdert een timer.
Na het aanroepen van deze functie word de timer niet meer uitgevoert en kun je de timer zijn id opnieuw gebruiken.
Parameters:
````C
int timerIndex = de id van de timer
````
Voorbeeld:
````C
void setup() {
  setTimer(0,500,timerCallback);//Defineer de timer
}

void loop() {
  maintainTimers();//Houd de timers up te date. Deze moet je aanroepen wil je dat de lib werkt.
}

void timerCallback(){
    clearTimer(0);//Stopt de timer waardoor deze code maar 1 keer is uitgevoert na 500ms
}
````

### maintainTimers
Definitie:
````C
void maintainTimers()
````
Deze functie moet je in je loop aanroepen als je wil dat de timers getriggert worden.
De functie controleerd van alle timers of ze getriggert moeten worden, als dat het geval is dan voert hij binnen deze functie de callback uit.

Voorbeeld:
````C
void loop() {
  maintainTimers();//Houd de timers up te date
}
````
### getTimerInterval
Definitie:
````C
long getTimerInterval(int timerIndex)
````
Retured de interval van de timer  
Parameters:
````C
int timerIndex = de id van de timer
````
Voorbeeld:
````C
setTimer(1,100,doSomething);
long interval = getTimerInterval(1);// interval will be 100ms in this case
````
