#ifndef Current_h
#define Current_h

#include <Arduino.h>

class Current {
  public:
    Current(int sensor, int pin);
    int getRawReading();
    float getUnfilteredCurrent();
    float getFilteredCurrent(int weight);
  private:
    int _sensor;
    int _pin;
    float _cleanCurrent;
};

#endif
