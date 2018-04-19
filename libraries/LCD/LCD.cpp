#include <LCD.h>

void LCD::printConsistency(float consistency) {
	setCursor(0,0);
	print("Consistency: ");
	print(consistency);
}