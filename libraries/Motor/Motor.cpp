#include <Motor.h>

Motor::Motor(int pwmPin, int IN1, int IN2) {
  _pwmPin = pwmPin;
  _IN1 = IN1;
  _IN2 = IN2;
  analogWrite(_IN1, HIGH);
  analogWrite(_IN2, LOW);
  _direction = 0;
}

void Motor::runMotor(int speed) {
  _pwm = int(speed*255/100);
  analogWrite(_pin, _pwm);
}

void Motor::stopMotor() {
  analogWrite(_pin, 0);
}

void Motor::reverseMotor() {
  if (_direction == 0) {
    analogWrite(_IN1, LOW);
    analogWrite(_IN2, HIGH);
    _direction = 1;
  }
  if (_direction == 1) {
    analogWrite(_IN1, LOW);
    analogWrite(_IN2, HIGH);
    _direction = 0;
  }
}
