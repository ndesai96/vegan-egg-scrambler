#include <Motor.h>

Motor::Motor(int pwmPin, int IN1, int IN2) {
  _pwmPin = pwmPin;
  _IN1 = IN1;
  _IN2 = IN2;
  digitalWrite(_IN1, LOW);
  digitalWrite(_IN2, HIGH);
}

void Motor::runMotor(int speed) {
  _pwm = int(speed*255/100);
  analogWrite(_pwmPin, _pwm);
}

void Motor::stopMotor() {
  analogWrite(_pwmPin, 0);
}

void Motor::direction1() {
    digitalWrite(_IN1, LOW);
    digitalWrite(_IN2, HIGH);
}

void Motor::direction2() {
    digitalWrite(_IN1, HIGH);
    digitalWrite(_IN2, LOW);
}
