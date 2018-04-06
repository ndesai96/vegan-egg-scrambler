#ifndef Motor_h
#define Motor_h

#include <Arduino.h>

class Motor {
  public:
    Motor(int pwmPin, int IN1, int IN2);
    void runMotor(int speed);
    void stopMotor();
    void reverseMotor();
  private:
    int _pin;
    int _pwm;
    int _pwmPin;
    int _IN1;
    int _IN2;
    int _direction;

};

#endif
