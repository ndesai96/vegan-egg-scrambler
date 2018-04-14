#include <Motor.h>
#include <Thermal.h>
#include <Current.h>
//#include <LiquidCrystal.h>
//#include <Proximity.h>

//Motor stir;
//Motor blend;
IRCamera amg;

// need to double check these pinouts

Current ina(169, 0);
Motor stir(9, 12, 8, 6/* need to add a dummy (?) trigger pin */);
Motor blend(5,11,7,4 /* fix PWM, IN1, IN2, trigger pins */);

unsigned long timestamp;
unsigned long stirStartTime;
unsigned long startTime;

//Proximity prox;

// current sensor parameters
float current;
float currentThreshold;
float unfilCurrent = 0;

//const int curNumReadings = 10; //size of readings array
//int readings[curNumReadings]; //readings from analog input
//int curReadIndex = 0; //index of the most recent current reading 
//int curTotal = 0; //running total
//int curAverage = 0; //average 
//int perCurExceedThreshold = 0; //%curent exceed threshold 
//int currentEnd = 0; 

int weight; 
float minCurrent;
float maxCurrent;
float consistency = 0;

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

// proximity sensor parameters
  
// progress parameters
int cookProgress = 0; 

void setup() {
  amg.begin();
  blend.begin();
  Serial.begin(9600);
  
  // blend for 30 seconds after getting user trigger
  blend.runMotor(100);
  delay(30000);
  blend.stopMotor();
  
//  averaging array buffer setup
//  for(int curThisReading=0; curThisReading < curNumReadings; curThisReading++) {
//    readings[curThisReading]=0;
//  }
}

void loop() {
   // store starting time of stirring
  if (firstLoop) {
    stirStartTime = millis();
    stir.primaryDirection();
    stir.runMotor(100);
    firstLoop = false;
  }
  
  // run in primary direction for 5 seconds
  stir.primaryDirection();
  startTime = millis();
  firstCycle = true;
  while (millis() - startTime < 5000) {
      
//    current sensor
//    setting up updating array 
//    curTotal = curTotal - readings[curReadIndex]; //subtract the last reading
//    readings[curReadIndex] = ina.getFilteredCurrent(weight);
//    unfilCurrent = ina.getUnfilteredCurrent();
//    curTotal = curTotal + readings[curReadIndex]; //add the reading to total
//    curReadIndex = curReadIndex + 1; //advance to the next position in the array
//    calculate the average
//    curAverage = curTotal/curNumReadings; 
//    end signal 
//    if (curAverage > currentThreshold) {
//    currentEnd = 1;
//    }
//    perCurExceedThreshold = curAverage/currentThreshold; 
//    if(perCurExceedThreshold > 1.5){
//    override = 1; 
//    }

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
  
  // check if consistency has exceeded threshold
  if (consistency > .3) {
    consistencyDone = true;
  }
  if (millis() - stirStartTime > 420000) {
  timeOverride = true;
  }
  if (false)/* PUT IN CONDITION FOR PROXIMITY SENSOR TRIGGERING */ {
    interferenceOverride = true;
  }

  // switch stirring directions
  stir.reverseDirection();
  startTime = millis();
  while (millis() < startTime) {
    delay(250);
  }
  if ((tempDone && consistencyDone) || interferenceOverride || timeOverride) {
    blend.stopMotor();
    stir.stopMotor();
    // display completion message on LCD display
    // send signal to piezobuzzer
    // go into an infinite delay loop to pseudo-stop the control system
    while (true) { 
      delay(1000);
    }
  }
  else {
    // currently only dependent on consistency
    cookProgress = int((consistency - 0.1) * (100 - 0) / (0.3 - 0.1) + 0);
  }
}

// display percentComplete on LCD display

//Proximity sensor 
  //determine if distance reading is greater than or equal to distance threshold
  //stop system or continue running

//Progress Update 
  //cookProgress = 0.5 *(curAverage/currentThreshold + tempAverage/tempThreshold); 
  //send progress to LCD

//overal system stop 
  //if((currentEnd & tempEnd & time > minTime) or override){
  //stop signal to motor 
  //signal to piezobuzzer 
  //}
