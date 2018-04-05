#include <Current.h>

Current::Current(int sensor, int pin) {
  _pin = pin;
  _sensor = sensor;
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

float Current::getFilteredCurrent(int weight) {
  _cleanCurrent = (weight*getUnfilteredCurrent() + (100-weight)*_cleanCurrent)/100.0;
  return _cleanCurrent;
}
