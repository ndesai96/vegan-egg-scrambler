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

float Current::getExpFilteredCurrent(int weight) {
  _cleanCurrent = (weight*getUnfilteredCurrent() + (100-weight)*_cleanCurrent)/100.0;
  return _cleanCurrent;
}

void Current::setCycleMinMaxCurrent(bool firstCycle, float unfilCurrent) {
  if (firstCycle) {
    _minCurrent = unfilCurrent;
    _maxCurrent = unfilCurrent;
  }
  else {
    _minCurrent = min(unfilCurrent, _minCurrent);
    _maxCurrent = max(unfilCurrent, _maxCurrent);
  }
}

float Current::getConsistency(unsigned long stirStartTime, int weight) {
  consistency = ((((_minCurrent*(1-((millis()-stirStartTime)/300000)))+_maxCurrent*((millis()-stirStartTime)/300000))*weight)+(consistency*(100-weight)))/100;
  return consistency;
}
