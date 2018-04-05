#include <Current.h>

Current::Current(int sensor, int pin, int weight) {
  _pin = pin;
  _sensor = sensor;
  _weight = weight;
  _cleanCurrent = 0;
}

int Current::getRawReading() {
  return analogRead(_pin);
}

float Current::getUnfilteredCurrent() {
  if (_sensor == 712) {
    return analogRead(_pin)*0.727 + 0.0195;
  }
  if (_sensor == 169) {
    return analogRead(_pin)*0.0049 + 0.0096;
  }
}

float Current::getFilteredCurrent() {
  _cleanCurrent = (_weight*getUnfilteredCurrent() + (100-_weight)*_cleanCurrent)/100.0;
  return _cleanCurrent;
}
