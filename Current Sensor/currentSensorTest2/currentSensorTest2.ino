
// current sensor analog pin
const int a0 = 0;

// controls motor speed
const int pwm = 9;

// default duty cycle
// motor range 80-255
const int duty = 128;

// controls motor direction
const int in1 = 6;
const int in2 = 7;

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

  Serial.println(analogRead(a0));

}
