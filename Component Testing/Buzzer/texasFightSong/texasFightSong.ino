/******************************************************************
 * SparkFun Inventor's Kit
 * Example sketch 11
 * 
 * BUZZER
 * 
 * This sketch uses the buzzer to play songs.
 * The Arduino's tone() command will play notes of a given frequency.
 * 
 * This sketch was written by SparkFun Electronics,
 * with lots of help from the Arduino community.
 * (This sketch was originally developed by D. Cuartielles for K3)
 * This code is completely free for any use.
 * Visit http://learn.sparkfun.com/products/2 for SIK information.
 * Visit http://www.arduino.cc to learn about the Arduino.
 * 
 * Version 2.0 6/2012 MDG
 * Version 2.1 9/2014 BCH
 *****************************************************************/

#include <Speaker.h>

Speaker speaker(2);

void setup() {
  speaker.begin();
}


void loop() {
  speaker.texasFight(33);
  speaker.flatTone(1000, 1000);
}





