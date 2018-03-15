#define windSensorPin 1
const double minLight = 0;
const double maxLight = 1024;

const double sensorLightRangeMin = 9;
const double sensorLightRangeMax = 1020;

int getLightInLux(){
  double value = (double)analogRead(windSensorPin);
  value = ((value - sensorLightRangeMin) / sensorLightRangeMax ) * (maxLight - minLight) + minLight;
  
  return round(value);
}

