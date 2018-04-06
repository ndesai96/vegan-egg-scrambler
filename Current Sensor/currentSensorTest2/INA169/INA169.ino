

#include "Current.h"

// current sensor analog pin
const int a0 = 0;

// controls motor speed
const int pwm = 9;

// default duty cycle
// motor range 80-255
float duty = 100;

// controls motor direction
const int in1 = 6;
const int in2 = 7;

int weight = 80;
int sensor = 169;

Current INA(sensor, a0);

//int raw_value; // container for analogRead value with offset
//float ampere;

//ExponentialFilter<float>FilteredCurrent(20,0);

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
  Serial.println(INA.getFilteredCurrent(weight));

}
