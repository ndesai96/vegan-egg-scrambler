//BASIC CODE FOR CONTROLLING MOTOR SPEED, HARD CODED SPEED 
int motorPin = 3;
int speed = 100;
 
void setup() 
{ 
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
 
} 
 
 
void loop() 
{ 
 
    if (speed >= 0 && speed <= 255)
    {
      analogWrite(motorPin, speed);
      delay(1000*30); //delay 30 seconds 
      speed= 0;
      analogWrite(motorPin,speed);
    }
  }

