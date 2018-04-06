#ifndef Motor_h
#define Motor_h

#include <Arduino.h>

class Motor {
  public:
    Motor(int pin);
    void runMotor(int speed);
    void stopMotor();
  private:
    int _pin;
    int _pwm;
};

#endif
