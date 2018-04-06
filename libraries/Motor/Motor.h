#ifndef Motor_h
#define Motor_h

#include <Arduino.h>

class Motor {
  public:
    Motor(int pwmPin, int IN1, int IN2);
    void runMotor(int speed);
    void stopMotor();
    void direction1();
    void direction2();
  private:
    int _pwmPin;
    int _IN1;
    int _IN2;
    int _pwm;
};

#endif
