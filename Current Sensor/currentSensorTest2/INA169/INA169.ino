

#include "Filter.h"

int raw_value; // container for analogRead value with offset
float ampere;

ExponentialFilter<float>FilteredCurrent(20,0);

void setup() {

  Serial.begin(9600);



}

void loop() {
  raw_value = analogRead(A1);
  ampere = 0.0049 * raw_value + 0.0096;

  float RawCurrent=ampere;
  FilteredCurrent.Filter(RawCurrent);
  float SmoothCurrent=FilteredCurrent.Current();
  
  Serial.println(SmoothCurrent);
  delay(100);

}
