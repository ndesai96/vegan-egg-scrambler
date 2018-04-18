#ifndef Proximity_h
#define Proximity_h

#include <Arduino.h>

class Proximity {
	public:
		Proximity(int trig, int echo);
		void begin();
		int getDistance();
		bool checkHand(); // returns TRUE if hand is present
	private:
		int _trig;
		int _echo;
};

#endif