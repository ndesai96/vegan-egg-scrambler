#include <LCD.h>

void LCD::printConsistency(float consistency) {
	setCursor(0,0);
	print("Consistency: ");
	print(consistency);
}

void LCD::printDistance(int distance) {
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
	
	for (int i = 5; i >= 0; i--) {
		setCursor(0,1);
		print(i);
		print(" seconds");
		delay(1000);
	}
	clear();
}