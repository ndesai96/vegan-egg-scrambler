#ifndef Current_h
#define Current_h

#include <Arduino.h>

class Current {
  public:
    Current(int sensor, int pin);
    int getRawReading();
    float getUnfilteredCurrent();
    float getExpFilteredCurrent(int weight);
    void setCycleMinMaxCurrent(bool firstCycle, float unfilCurrent);
    void getConsistency(unsigned long stirStartTime, int weight);
    float consistency;
  private:
    int _sensor;
    int _pin;
    float _cleanCurrent;
    float _minCurrent;
    float _maxCurrent;
};

#endif
