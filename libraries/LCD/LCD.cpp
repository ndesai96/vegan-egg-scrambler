#include <LCD.h>

void LCD::printConsistTemp(float consistency, float temperature) {
	clear();
	setCursor(0,0);
	print("Consist: ");
	print(consistency);
	print("%");
	setCursor(0,1);
	print("Temp: ");
	print(temperature);
	print("%");
}

void LCD::printDistance(int distance) {
	clear();
	setCursor(0,1);
	print("Distance: ");
	print(distance);
	print(" in");
}

void LCD::printAlert() {
	clear();
	setCursor(0,0);
	print("ALERT!!");
	setCursor(0,1);
	print("Hand Detected");
}

void LCD::printCountdown() {
	clear();
	setCursor(0,0);
	print("Resuming in:");

	for (int i = 3; i >= 0; i--) {
		setCursor(0,1);
		print(i);
		print(" seconds");
		delay(1000);
	}
	clear();
	setCursor(0,0);
	print("Stirring");
}

void LCD::printBlendCountdown(int blendTime) {
	clear();
	setCursor(0,0);
	print("Blending");
	int seconds = blendTime / 1000;

	for (int i = seconds; i >= 0; i--) {
		setCursor(0,1);
		print("complete in ");
		print(i);
		print("s   ");
		delay(1000);
	}

	clear();
	setCursor(0,0);
	print("Done Blending");
	setCursor(0,1);
	print("Ready to Stir");

}

void LCD::printStirCountdown(int initDelay) {
	clear();
	setCursor(0,0);
	int seconds = initDelay / 1000;

	for (int i = seconds; i >= 0; i--) {
		print("Stirring in ");
		print(i);
		print("s");
		delay(1000);
		clear();
	}

	clear();
	setCursor(0,0);
	print("Stirring");
}

void LCD::printProgression(int completion) {
	clear();
	setCursor(0,0);
	print(completion);
	print("%");
	print(" Complete");
}
