#include <Motor.h>

Motor blenderstir(1, 1, 2); //int pwmPin, 1 is dummy variable, 2 is dummy variable

//initialize a physical switch
const int switchPin = 2; 
int switchState = 0;   //variable for reading the switch status

void setup()
{
  pinMode(switchPin, INPUT); //initialize the switch as an input
  
 
  Serial.begin(9600);

}


void loop()
{
  switchState = digitalRead(switchPin);
  if(switchState == HIGH) {
     blenderstir.runMotor(100);
     delay(1000 * 45); //delay 45 seconds
   blenderstir.runMotor(0);  //turn motor off
   switchState = 0; //attempt to prevent endless looping by overriding the switch signal 
  }
  
}

