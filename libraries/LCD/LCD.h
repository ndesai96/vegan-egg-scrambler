#ifndef LCD_h
#define LCD_h

#include <Arduino.h>
#include <LiquidCrystal.h>

class LCD : public LiquidCrystal {
	public:
		using LCD::LCD;
		void printConsistency(float consistency);
};

#endif