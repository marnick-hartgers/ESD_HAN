int analogPin = 0;
int val = 0;
float gem;
int ledPin = 10;

int outputval = 0;

void setup()
{
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  val = analogRead(analogPin);
  gem = gem + (val - gem) / 1000;
  outputval = abs(val - round(gem));
  outputval = constrain(pow(outputval,outputval), 0 ,255);
  analogWrite(ledPin, outputval);
}
