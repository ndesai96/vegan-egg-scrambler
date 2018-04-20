#include <Motor.h>
#include <Thermal.h>
#include <Current.h>
#include <LiquidCrystal.h>
#include <Proximity.h>
#include <Speaker.h>

// Arduino Pins
const int stir_pwm = 4, stir_in1 = 24, stir_in2 = 26, stir_trig = 35;     // stirring motor
const int blend_pwm = 5, blend_in1 = 52, blend_in2 = 53, blend_trig = 31; // blender motor

const int current_sensor = 169, current_data = 0; // current sensor
const int rs = 25, en = 6, d4 = 8, d5 = 27, d6 = 3, d7 = 22; // lcd
const int trig = 23, echo = 29;
const int buzzerPin = 2; 
=======
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
float consistencyThreshold = 0.6;
float unfilCurrent = 0;
int   weight; 
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
int percentConsistency;
int percentTime;
int percentComplete = 0; 

void setup() {
  amg.begin();
  blend.begin();
  proximity.begin();
  speaker.begin();
  lcd.begin(16, 2);
  Serial.begin(9600); 
}

void loop() {
<<<<<<< HEAD
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration*0.0133/2;

  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" in");
<<<<<<< HEAD
  pinMode(buzzer, OUTPUT);
  
  // blend for 30 seconds after getting user trigger
  blend.runMotor(100);
  delay(30000);
  blend.stopMotor();

  //pinMode(buzzer,OUTPUT);
}

void loop() {
=======
>>>>>>> 61f0e1b8ec81f7886624dac2539c0938fffdd9d2
   // store starting time of stirring
=======
>>>>>>> 33ab3420580e28b19f2877924ce063a40e1390e0

//  lcd.setCursor(0, 0);
//  lcd.print("Distance: ");
//  lcd.print(distance);
//  lcd.print(" in");

  // first loop begins/finishes blending and begins stirring
  if (firstLoop) {
    // run blender cycle after user input
    blend.waitForTrigger();
    blend.runMotor(100);
    delay(45000);
    blend.stopMotor();

    // notify user that blending is done
    speaker.flatTone(1000, 3000);

    // stir eggs after user input
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
    
//    distance = proximity.getDistance();
//    lcd.setCursor(0, 0);
//    lcd.print("Distance: ");
//    lcd.print(distance);
//    lcd.print(" in");
    proximity.handCheck(stir);
    unfilCurrent = ina.getUnfilteredCurrent();
    if ((unfilCurrent > .1) && (unfilCurrent < .5)) {
      ina.setCycleMinMaxCurrent(firstCycle, unfilCurrent);
    }
    amg.readPixels(pixels);
  
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
    
    if (firstCycle) {
      firstCycle = false;    
    }
  }

  // check completion conditions
  if (consistencyDone == false) {
    if (ina.getConsistency(stirStartTime, weight) > consistencyThreshold) {
      consistencyDone = true;
    }
  }
  if (millis() - stirStartTime > 480000) {
    timeOverride = true;
  }
  if (tempDone == false) {
    // CHECK TEMPERATURE AND COMPARE TO THRESHOLD
    // tempDone == true;
  }
  if ((tempDone && consistencyDone) || interferenceOverride || timeOverride) {
    stir.stopMotor();
<<<<<<< HEAD
    // display completion message on LCD display
    // send signal to piezobuzzer
    tone(buzzer,1000);
    delay(1000);
    noTone(buzzer);
    delay(1000); 
    // go into an infinite delay loop to pseudo-stop the control system
    while (true) { 
      delay(1000);
    }
=======
    // display 100% percent complete message on LCD display
    speaker.texasFight(33);
    while (true) {} // infinite loop to delay until reset
>>>>>>> 33ab3420580e28b19f2877924ce063a40e1390e0
  }
  else {
    // currently percentCompletion on consistency
    percentConsistency = int((ina.consistency - 0.1) * 100 / (consistencyThreshold - 0.1));
    percentTime = millis()*100/480000;
    percentComplete = max(percentConsistency, percentTime); 
    // display percentageComplete on LCD display
  }
  
  // runs stirring in reverse direction
  stir.reverseDirection();
  startTime = millis();
  while (millis() - startTime < 3000) {
    proximity.handCheck(stir);
    delay(250);
  }

}
<<<<<<< HEAD

// display percentComplete on LCD display

//Proximity sensor 
  //determine if distance reading is greater than or equal to distance threshold
  //stop system or continue running

//Progress Update 
  //cookProgress = 0.5 *(curAverage/currentThreshold + tempAverage/tempThreshold); 
  //send progress to LCD

//overal system stop 
 //if((currentEnd & tempEnd & time > minTime) or override);{
  //stop signal to motor 
  //signal to piezobuzzer 
  //}
=======
>>>>>>> 33ab3420580e28b19f2877924ce063a40e1390e0
