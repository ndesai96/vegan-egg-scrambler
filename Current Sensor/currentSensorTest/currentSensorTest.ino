int analogPin = 0;
double value;
double offset = 0;

void setup() {

  // number of initial values to average when determining DC offset
  int offsetAvgSize = 15;

  // determine DC offset
  for (int i = 0; i <= offsetAvgSize; i++) {
    offset = offset + analogRead(analogPin);
    delay(5); // short pause between reads
  }
  offset = offset / offsetAvgSize;

  // start serial output
  Serial.begin(9600); // baud rate of 9600
}

void loop() {
  // read and adjust raw value reading from sensor
  value = analogRead(analogPin) - offset;

  // print results to serial monitor
  Serial.print(value);
  Serial.print("\n");

  // sleep
  delay(1000);
}
