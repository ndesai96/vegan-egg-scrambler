#include <Proximity.h>

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

	digitalWrite(_trig, LOW);
  	delayMicroseconds(2);
  	digitalWrite(_trig, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(_trig, LOW);

  	duration = pulseIn(_echo, HIGH);
  	distance = duration*0.0133/2;

  	return distance;

}

bool Proximity::handCheck() {
	distance = getDistance();
	if (distance < 11) {
		return true;
	}

	else {
		return false;
	}

}

void Proximity::handReact(Motor &stir, LCD &lcd) {
	
	if (handCheck()) {
		stir.stopMotor();
		lcd.printAlert();
		while (handCheck()) {
			delay(1000);
		}

		lcd.printCountdown();

		while (handCheck()) {
			lcd.print("Remove Hand!!");
			lcd.clear();
		}

		stir.primaryDirection();
		stir.runMotor(100);
	}
	
}
