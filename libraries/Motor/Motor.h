#ifndef Motor_h
#define Motor_h

#include <Arduino.h>

class Motor {
  public:
    Motor(int pwmPin, int IN1, int IN2, int trigger);
    void begin();
    void waitForTrigger();
    void runMotor(int speed);
    void stopMotor();
    void primaryDirection();
    void reverseDirection();
  private:
    int _pwmPin;
    int _IN1;
    int _IN2;
    int _trigger;
    int _pwm;
};

#endif
