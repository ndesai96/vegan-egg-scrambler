#include <Wire.h>
#include <Adafruit_AMG88xx.h>

Adafruit_AMG88xx amg;

float percentThreshold = 70;
float tempThreshold = 75; // in degC

float dataPoints[AMG88xx_PIXEL_ARRAY_SIZE];
float percentOver;

void setup() {
  Serial.begin(9600);
  status = amg.begin();
  if (!status) {
    serial.println("IR camera not connected.");
    while (1);
  }
}

void loop() {
  amg.readPixels(dataPoints);

// METHOD 1: CHECKS FOR NUMBER OF PIXELS OVER THE TEMP THRESHOLD
  int overThreshold = 0;
  for (int i = 0; i < AMG88xx_PIXEL_ARRAY_SIZE; i++) {
    if (dataPoints[i] > tempThreshold) {
      overThreshold++;      
    }
  }
  percentOver = overThreshold * 100 / AMG88xx_PIXEL_ARRAY_SIZE;
  if (percentOver > percentThreshold) {
    println("Eggs are done!");
    while (1);
  }
  else {
    println(percentOver);
  }

// METHOD 2: COMPARES AVERAGE TEMPERATURE TO TEMP THRESHOLD
  float averageTemp = 0;
  for (int i = 0; i < AMG88xx_PIXEL_ARRAY_SIZE; i++) {
    averageTemp = averageTemp + dataPoints[i];
  }
  averageTemp = averageTemp / AMG88xx_PIXEL_ARRAY_SIZE;

  if (averageTemp > tempThreshold) {
    println("Eggs are done!");
    while (1);
  }
  else {
    println(averageTemp);
  }

// METHOD 3: FILTER EXTREME VALUES BEFORE COMPARING AVERAGE TEMPERATURE TO TEMP THRESHOLD
  float averageTemp = 0;
  int counter = 0;
  for (int i = 0; i < AMG88xx_PIXEL_ARRAY_SIZE; i++) {
    if (dataPoints[i] < 150 &&  dataPoints[i] > 30) {
      averageTemp = averageTemp + dataPoints[i];
      counter++;
    }
  }
  if (counter > 0) {
    averageTemp = averageTemp / counter;
  }
  if (counter = 0) {
    averageTemp = 26
  }
  if (averageTemp > tempThreshold) {
    println("Eggs are done!");
    while (1);
  }
  else {
    println(averageTemp);
  }
}
