#include <Motor.h>

Motor::Motor(int pin) {
  _pin = pin;
}

void Motor::runMotor(int speed) {
  _pwm = int(speed*255/100);
  analogWrite(_pin, _pwm);
}

void Motor::stopMotor() {
  analogWrite(_pin, 0);
}
