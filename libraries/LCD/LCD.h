#ifndef LCD_h
#define LCD_h

#include <Arduino.h>
#include <LiquidCrystal.h>

class LCD : public LiquidCrystal {
	public:
		using LiquidCrystal::LiquidCrystal;
		void printProgression(float consistency, float temperature);
		void printDistance(int distance);
		void printAlert();
		void printCountdown();
};

#endif