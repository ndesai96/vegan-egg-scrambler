#include <Motor.h>
#include <Thermal.h>
#include <Current.h>
#include <LCD.h>
#include <Proximity.h>
#include <Speaker.h>

// Arduino Pins
const int stir_pwm = 4, stir_in1 = 24, stir_in2 = 26, stir_trig = 35;     // stirring motor
const int blend_pwm = 5, blend_in1 = 52, blend_in2 = 53, blend_trig = 31; // blender motor


const int current_sensor = 169, current_data = 0; // current sensor
const int rs = 25, en = 6, d4 = 8, d5 = 27, d6 = 3, d7 = 22; // lcd
const int trig = 23, echo = 29;
const int speaker_pin = 2; 

// Object Initialization
Motor stir(stir_pwm, stir_in1, stir_in2, stir_trig);
Motor blend(blend_pwm, blend_in1, blend_in2,blend_trig);
Current ina(current_sensor, current_data);
LCD lcd(rs, en, d4, d5, d6, d7);
Proximity proximity(trig, echo);
IRCamera amg;
Speaker speaker(speaker_pin);

unsigned long stirStartTime;
unsigned long startTime;

int delayTime = 0;
int initDelayTime = 5000;


// current sensor parameters
float consistencyThreshold = 0.26;
float unfilCurrent;
int   weight = 60; 
int   crossedConsistencyThreshold = 0;

// binary flags
bool firstLoop = true;
bool firstCycle = true;
bool consistencyDone = false; 
bool tempDone = false;
bool timeOverride = false;
bool interferenceOverride = false; // for proximity sensor

// IR camera parameters
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
int   pixelLocation[16]= {11,12,13,19,20,21,28,29,36,37,43,44,45,51,52,53}; // array indices
int   tempCounter = 0;
float averageTemp;
float tempThreshold;
  
// progress parameters
int percentConsistency;
int percentTemperature;
int percentTime;
int percentComplete; 

void setup() {
  amg.begin();
  blend.begin();
  proximity.begin();
  speaker.begin();
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Ready to Blend");
  Serial.begin(9600); 
}

void loop() {

  // first loop begins/finishes blending and begins stirring
  if (firstLoop) {
    // run blender cycle after user input
   
    blend.waitForTrigger();
    
    blend.runMotor(100);
    lcd.printBlendCountdown(30000);
    blend.stopMotor();

    // notify user that blending is done
    speaker.flatTone(1000, 1500);

    // stir eggs after user input
    stir.waitForTrigger();

    lcd.printStirCountdown(initDelayTime);
    
    stirStartTime = millis();
    stir.primaryDirection();
    stir.runMotor(100);
    firstLoop = false;
  }

  // run stirring in primary direction for 5 seconds
  stir.primaryDirection();
  startTime = millis();
  firstCycle = true;
  while (millis() - startTime < 5000) {

    proximity.handReact(stir, lcd);
    unfilCurrent = ina.getUnfilteredCurrent();
    if ((unfilCurrent > .1) && (unfilCurrent < .5)) {
      ina.setCycleMinMaxCurrent(firstCycle, unfilCurrent);
      firstCycle = false;
    }
    amg.readPixels(pixels);
  
    //Print time, unfiltered current, and temperature array to serial monitor 
    Serial.print((millis()-stirStartTime));
    Serial.print(",");

    Serial.print(unfilCurrent);
    Serial.print(",");
  
    for(int j = 0; j < 64 ; j++){
      Serial.print(pixels[j]);
      Serial.print(",");  
    }
    Serial.println("");
    delay(250); 
  }

  ina.getConsistency(stirStartTime, weight);

  // print consistency to serial monitor
  Serial.print((millis()-stirStartTime));
  Serial.print(",");
  Serial.print(ina.consistency);
  Serial.print(",");
  for(int j = 0; j < 64 ; j++){
    Serial.print("0");
    Serial.print(",");  
  }
  Serial.println("");
  
  // check consistency
  if (consistencyDone == false) {
    
    percentConsistency = min(int((ina.consistency - 0.1) / (consistencyThreshold - 0.1) * 100), 100);
    
    if (ina.consistency >= consistencyThreshold) {
      crossedConsistencyThreshold = crossedConsistencyThreshold + 1;
    }
    if (crossedConsistencyThreshold > 2) {
      consistencyDone = true;
    }
  }

  // CHECK TEMPERATURE
  if (tempDone == false) {
    for (int i =0;i<16;i++) {
       if(pixels[pixelLocation[i]] >= 66) {  // the pixel's temperature value must be greater than or equal 66
         tempCounter = tempCounter + 1;
       } 
    }

    percentTemperature = min(int(tempCounter / 8 * 100), 100);
    
    if(tempCounter >= 8) { 
     tempDone = true;
    }
    else {
      tempCounter = 0;
    }
  }
  
  // CHECK TIME
  if ((millis() - stirStartTime) > 540000) {
    timeOverride = true;
  }
  percentTime = (millis()-stirStartTime)*100/540000;

  // DISPLAY COMPLETION PERCENTAGE
  percentComplete = max(min(percentConsistency, percentTemperature), percentTime);
  lcd.printConsistTemp(percentConsistency, percentTemperature); 

  // check completion
  if ((tempDone && consistencyDone) || timeOverride) {
    stir.stopMotor();
    // display 100% percent complete message on LCD display
    speaker.texasFight(33);
    while (true) {} // infinite loop to delay until reset
  }

  // runs stirring in reverse direction
  stir.reverseDirection();
  startTime = millis();
  while (millis() - startTime < 3000) {
      proximity.handReact(stir, lcd);
    delay(250);
  }
  stir.stopMotor();
  delay(delayTime);
  stir.runMotor(100);

}
