const int buttonPin = 2; 
const int motorPin = 8;

int buttonState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(motorPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin); 

  if(buttonState == HIGH);
  else {
    digitalWrite(motorPin, LOW);
  }
}
