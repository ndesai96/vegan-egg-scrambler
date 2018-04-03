#include <Wire.h>
// NOTE!!!!!!!!!!!!!!!!!!! 
// YOU NEED TO INSTALL THE ADAFRUIT AMG88xx LIBRARY IN ORDER TO USE THIS CODE
#include <Adafruit_AMG88xx.h>

Adafruit_AMG88xx amg;

float dataPoints[AMG88xx_PIXEL_ARRAY_SIZE];

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

  // prints results visualizable as an 8x8 array
  Serial.print("[");
  for(int i=1; i<=AMG88xx_PIXEL_ARRAY_SIZE; i++){
    Serial.print(dataPoints[i-1]);
    Serial.print(", ");
    if( i%8 == 0 ) Serial.println();
  }
  Serial.println("]\n");
}
