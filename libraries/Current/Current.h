#ifndef Current_h
#define Current_h

#include <Arduino.h>

class Current {
  public:
    Current(int sensor, int pin, int weight);
    int getRawReading();
    float getUnfilteredCurrent();
    float getFilteredCurrent();
  private:
    int _sensor;
    int _pin;
    int _weight;
    float _cleanCurrent;
};

#endif
