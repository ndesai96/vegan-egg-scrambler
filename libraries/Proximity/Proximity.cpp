#include <Proximity.h>
#include <Motor.h>

Proximity::Proximity(int trig, int echo) {
	_trig = trig;
	_echo = echo;
}

void Proximity::begin() {
	pinMode(_trig, OUTPUT);
	pinMode(_echo, INPUT);
}

int Proximity::getDistance() {

	long duration;
	int distance;

	digitalWrite(_trig, LOW);
  	delayMicroseconds(2);
  	digitalWrite(_trig, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(_trig, LOW);

  	duration = pulseIn(_echo, HIGH);
  	distance = duration*0.0133/2;

  	return distance;

}

void Proximity::handCheck(Motor &stir) {
	if (getDistance() < 11) {
		stir.stopMotor();
		while (true) {
			delay(100);
		}
	}
}
