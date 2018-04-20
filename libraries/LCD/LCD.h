#ifndef LCD_h
#define LCD_h

#include <Arduino.h>
#include <LiquidCrystal.h>

class LCD : public LiquidCrystal {
	public:
		using LiquidCrystal::LiquidCrystal;
		void printConsistency(float consistency);
		void printDistance(int distance);
		void printAlert();
		void printCountdown();
};

#endif