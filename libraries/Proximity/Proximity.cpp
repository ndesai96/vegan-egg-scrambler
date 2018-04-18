#include <Proximity.h>

Proximity::Proximity(int trig, int echo) {
	_trig = trig;
	_echo = echo;
}

void Proximity::begin() {
	pinMode(_trig, OUTPUT);
	pinMode(_echo, INPUT);
}

int getDistance() {
	
	long duration;
	int distance;

	digitalWrite(trig, LOW);
  	delayMicroseconds(2);
  	digitalWrite(trig, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(trig, LOW);
  	
  	duration = pulseIn(echo, HIGH);
  	distance = duration*0.0133/2;

  	return distance;

}

bool checkHand() {

	// returns TRUE if Hand is present
	int distance;
	int max_distance = 11;

	distance = getDistance();

	if (distance < max_distance) {
		return true;
	}

	else {
		return false;
	}

}