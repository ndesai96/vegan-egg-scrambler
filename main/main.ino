#include <Motor.h>
#include <Thermal.h>
#include <Current.h>
#include <LiquidCrystal.h>
#include <Proximity.h>
#include <Speaker.h>

// Arduino Pins
const int stir_pwm = 4, stir_in1 = 24, stir_in2 = 26, stir_trig = 35;     // stirring motor
const int blend_pwm = 5, blend_in1 = 52, blend_in2 = 53, blend_trig = 31; // blender motor
const int current_sensor = 169, current_data = 0;                         // current sensor
const int rs = 25, en = 6, d4 = 8, d5 = 27, d6 = 3, d7 = 22;              // lcd display
const int trig = 23, echo = 29;                                           // proximity sensor
const int speaker_pin = 2;                                                // speaker

// Object Initialization
Motor stir(stir_pwm, stir_in1, stir_in2, stir_trig);
Motor blend(blend_pwm, blend_in1, blend_in2,blend_trig);
Current ina(current_sensor, current_data);
Proximity proximity(trig, echo);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
IRCamera amg;
Speaker speaker(speaker_pin);

unsigned long timestamp;
unsigned long stirStartTime;
unsigned long startTime;

// proximity parameters
int distance;

// current sensor parameters
float current;
float currentThreshold;
float unfilCurrent = 0; 

int weight; 
float minCurrent;
float maxCurrent;
float consistency = 0;

// binary flags
bool firstLoop = true;
bool firstCycle = true;
bool consistencyDone = false; 
bool tempDone = false;
bool timeOverride = false;
bool interferenceOverride = false; // for proximity sensor

// IR camera parameters
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
float averageTemp;
float tempThreshold;
  
// progress parameters
int cookProgress = 0; 

void setup() {
  amg.begin();
  blend.begin();
  proximity.begin();
  speaker.begin();
  lcd.begin(16, 2);
  Serial.begin(9600); 
}

void loop() {
  
  distance = proximity.getDistance();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" in");

  // first loop begins/finishes blending and begins stirring
  if (firstLoop) {
    blend.waitForTrigger();
    blend.runMotor(100);
    delay(10000);
    blend.stopMotor();

    speaker.flatTone(1000, 3000);

    stir.waitForTrigger();
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

    distance = proximity.getDistance();
    lcd.setCursor(0, 0);
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.print(" in");
    
    unfilCurrent = ina.getUnfilteredCurrent();
    
    if (firstCycle) {
      minCurrent = unfilCurrent;
      maxCurrent = unfilCurrent;
      firstCycle = false;    
    }
    else {
      minCurrent = min(unfilCurrent, minCurrent);
      maxCurrent = max(unfilCurrent, maxCurrent);
    }

    /*
    ina.setMinMaxCurrent(firstCycle, unfilCurrent);
    firstCycle = false;
    */
        
    // IR camera 
    amg.readPixels(pixels);
    //implement a similar running average, but decide which pixels to samples 
    //end signal 
    
    //Print to serial monitor 
    timestamp = millis();
    Serial.print(timestamp);
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
  
  // exponentially-filtered time-weighted consistency
  consistency = ((((minCurrent*(1-((millis()-stirStartTime)/300000)))+maxCurrent*((millis()-stirStartTime)/300000))*weight)+(consistency*(1-weight)))/100;
  // consistency = ina.getConsistency(stirStartTime, weight);
  
  // check if consistency has exceeded threshold
  /*
  if (consistency > .3) {
    consistencyDone = true;
  }
  */
  if (millis() - stirStartTime > 420000) {
    timeOverride = true;
  }
  
  /*
  if (false) { // PUT IN CONDITION FOR PROXIMITY SENSOR TRIGGERING
    interferenceOverride = true;
  }
  */
  
  // runs stirring in reverse direction
  stir.reverseDirection();
  startTime = millis();
  
  while (millis() - startTime < 3000) {
    
    distance = proximity.getDistance();
    lcd.setCursor(0, 0);
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.print(" in");
    
    delay(250);
  }
  /*
  if ((tempDone && consistencyDone) || interferenceOverride || timeOverride) {
    blend.stopMotor();
    stir.stopMotor();
    // display percent complete message on LCD display
    speaker.texasFight(33);
    // go into an infinite delay loop to pseudo-stop the control system
    while (true) { 
      delay(1000);
    }
  }
  else {
    // currently only dependent on consistency
    cookProgress = int((consistency - 0.1) * (100 - 0) / (0.3 - 0.1) + 0);
  }
  */
}
