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