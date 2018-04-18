#ifndef Current_h
#define Current_h

#include <Arduino.h>

class Current {
  public:
    Current(int sensor, int pin);
    int getRawReading();
    float getUnfilteredCurrent();
    float getExpFilteredCurrent(int weight);
    void setMinMaxCurrent(bool firstCycle, float unfilCurrent);
    float getConsistency(unsigned long stirStartTime, int weight);

  private:
    int _sensor;
    int _pin;
    float _cleanCurrent;
    float minCurrent;
    float maxCurrent;
    float consistency;
};

#endif
