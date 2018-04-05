

#include "Filter.h"

// current sensor analog pin
const int a0 = 0;

// controls motor speed
const int pwm = 9;

// default duty cycle
// motor range 80-255
float duty = 175;

// controls motor direction
const int in1 = 6;
const int in2 = 7;

int raw_value; // container for analogRead value with offset
float ampere;

ExponentialFilter<float>FilteredCurrent(20,0);

void setup() {

  Serial.begin(9600);

   pinMode(pwm, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  Serial.begin(9600);

  // intialize motor direction
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

}

void loop() {

analogWrite(pwm, duty);
  
  raw_value = analogRead(A1);
  ampere = 0.0049 * raw_value + 0.0096;

  float RawCurrent=ampere;
  FilteredCurrent.Filter(RawCurrent);
  float SmoothCurrent=FilteredCurrent.Current();
  
  Serial.println(SmoothCurrent);
  //delay(100);

}
