#include <Motor.h>

Motor::Motor(int pin) {
  _pin = pin;
}

Motor::runMotor(int speed) {
  _pwm = int(speed*255/100);
  analogWrite(_pin, _pwm);
}

Motor::stopMotor() {
  analogWrite(_pin, 0);
}
