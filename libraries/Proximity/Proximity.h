#ifndef Proximity_h
#define Proximity_h

#include <Motor.h>
#include <Arduino.h>
#include <LCD.h>

class Proximity {
	public:
		Proximity(int trig, int echo);
		void begin();
		int getDistance();
		bool handCheck();
		void handReact(Motor &stir, LCD &lcd);
		int distance;
	private:
		int _trig;
		int _echo;
};

#endif
