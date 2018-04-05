//#include <Motor.h>
#include <Thermal.h>
#include <Current.h>
#include <LiquidCrystal.h>
//#include <Proximity.h>

//Motor stir;
//Motor blend;
IRCamera amg;
Current ina(169, 0, 20);

//Proximity prox;

// current sensor parameters
float current;
float currentThreshold;

// IR camera parameters
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
float averageTemp;
float TempThreshold;

void setup() {
  amg.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  amg.readPixels(pixels);
  current = ina.getFilteredCurrent();
}
