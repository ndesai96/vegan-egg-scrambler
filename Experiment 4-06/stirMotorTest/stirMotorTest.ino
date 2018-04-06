#include <Motor.h>
Motor stir(9, 12, 8); 


void setup() {
  // put your setup code here, to run once:
stir.runMotor(100);
}

void loop() {
  // put your main code here, to run repeatedly:
stir.direction2(); 
delay(1000); 
stir.direction1(); 
delay(1000); 
}
