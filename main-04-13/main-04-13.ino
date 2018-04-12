#include <Motor.h>
#include <Thermal.h>
#include <Current.h>
//#include <LiquidCrystal.h>
//#include <Proximity.h>

IRCamera amg;         //IR Camera
Current ina(169, 0);  //Current Sensor
Motor stir(9, 12, 8); // DC Scrambling Motor

unsigned long timestamp; // Timestamp

//Proximity prox;

// Current sensor parameters
float unfilCurrent;
float weight; 
float filCurrent;

// IR camera parameters
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
float averageTemp;
float tempThreshold;

//progress parameters
double cookProgess; 

void setup() {
  amg.begin();
  stir.direction2();
  stir.runMotor(100);
  
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 20; i++) {

    // Current sensor
    unfilCurrent = ina.getUnfilteredCurrent();
      
    // IR camera 
    amg.readPixels(pixels);
    
    // Print to serial monitor 
    // Timestamp
    timestamp = millis();
    Serial.print(timestamp);
    Serial.print(",");

    // Current
    Serial.print(unfilCurrent);
    Serial.print(",");

    // Temperature
    for(int j = 0; j < 64 ; j++){
      Serial.print(pixels[j]);
      Serial.print(",");  
    }
    
    Serial.println("");
    delay(500);
  }
  
  stir.direction1();
  for (int i = 0; i < 10; i++) {
    delay(500);
  }
  stir.direction2();
}
