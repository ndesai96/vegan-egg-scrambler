#ifndef Proximity_h
#define Proximity_h

#include <Motor.h>
#include <Arduino.h>

class Proximity {
	public:
		Proximity(int trig, int echo);
		void begin();
		int getDistance();
		void handCheck(Motor &stir);
	private:
		int _trig;
		int _echo;
};

#endif
