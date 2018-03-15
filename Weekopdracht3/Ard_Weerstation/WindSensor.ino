#define windSensorPin 0
const double minAngle = 0;
const double maxAngle = 360;

const double sensorWindRangeMin = 0;
const double sensorWindRangeMax = 1023;

int getWindDirection(){
  double value = (double)analogRead(windSensorPin);
  value = ((value - sensorWindRangeMin) / sensorWindRangeMax ) * (maxAngle - minAngle) + minAngle;
  return round(value);
}

