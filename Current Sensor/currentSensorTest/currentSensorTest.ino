int analogPin = 0;
double raw_value;
double current;
double offset = 511.0;

void setup() {

  // start serial output
  Serial.begin(9600); // baud rate of 9600
}

void loop() {
  // read and adjust raw value reading from sensor
  raw_value = analogRead(analogPin) - offset;
  current = (raw_value*.0727) + 0.0195;

  // print results to serial monitor
  Serial.println(current);

  // sleep
  delay(1000);
}
