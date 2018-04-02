
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
const float raw_offset = 511.0; // experimentally determined DC offset for current sensor
const float cal_m = 0.727; // calibration coefficient
const float cal_b = 0.0195; // calibration offset
 float current=0; //

ExponentialFilter<float>FilteredCurrent(10,0);

void setup() {
  
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

         // read and adjust raw value reading from sensor
      raw_value = analogRead(a0) - raw_offset;
      current = (raw_value*cal_m) + cal_b;

  float RawCurrent=current;
  FilteredCurrent.Filter(RawCurrent);
  float SmoothCurrent=FilteredCurrent.Current();

  if(abs(SmoothCurrent)>1.1) {
    duty=0;
  }
  else {
    duty=175;
  }

  Serial.println(SmoothCurrent);
  delay(1000);

}
