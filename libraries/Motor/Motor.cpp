#include <Motor.h>

Motor::Motor(int pwmPin, int IN1, int IN2, int trigger) {
  _pwmPin = pwmPin;
  _IN1 = IN1;
  _IN2 = IN2;
  _trigger = trigger;

}

void::Motor::begin() {
  pinMode(_trigger, INPUT);
}

void Motor::waitForTrigger() {
  while (digitalRead(_trigger) == LOW) {
    delay(500);
  }
}

void Motor::runMotor(int speed) {
  _pwm = int(speed*255/100);
  analogWrite(_pwmPin, _pwm);
}

void Motor::stopMotor() {
  analogWrite(_pwmPin, 0);
}

void Motor::primaryDirection() {
    digitalWrite(_IN1, HIGH);
    digitalWrite(_IN2, LOW);
}


void Motor::reverseDirection() {
    digitalWrite(_IN1, LOW);
    digitalWrite(_IN2, HIGH);
}
