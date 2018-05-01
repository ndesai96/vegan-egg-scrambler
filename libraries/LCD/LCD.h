#ifndef LCD_h
#define LCD_h

#include <Arduino.h>
#include <LiquidCrystal.h>

class LCD : public LiquidCrystal {
	public:
		using LiquidCrystal::LiquidCrystal;
		void printConsistTemp(float consistency, float temperature);
		void printDistance(int distance);
		void printAlert();
		void printCountdown();
		void printBlendCountdown(int blendTime);
		void printStirCountdown(int initDelay);
		void printProgress(int completion);
};

#endif