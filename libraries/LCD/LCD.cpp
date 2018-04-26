#include <LCD.h>

void LCD::printProgression(float consistency, float temperature) {
	clear();
	setCursor(0,0);
	print("Consist: ");
	print(consistency);
	//print("%");
	setCursor(0,1);
	print("Temp: ");
	print(temperature);
	//print("%");
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
}
