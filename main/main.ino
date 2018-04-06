#include <Motor.h>
#include <Thermal.h>
#include <Current.h>
//#include <LiquidCrystal.h>
//#include <Proximity.h>

//Motor stir;
//Motor blend;
IRCamera amg;
Current ina(169, 0);
Motor stir(9, 12, 13);


//Proximity prox;

// current sensor parameters
float weight; 
float current;
float currentThreshold;
float unfilCurrent = 0;

const int curNumReadings = 10; //size of readings array
int readings[curNumReadings]; //readings from analog input
int curReadIndex = 0; //index of the most recent current reading 
int curTotal = 0; //running total
int curAverage = 0; //average 
int perCurExceedThreshold = 0; //%curent exceed threshold 
int currentEnd = 0; 
int override = 0; 


// IR camera parameters
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
float averageTemp;
float tempThreshold;

//proximity sensor parameters

//progress parameters
double cookProgess = 0; 

void setup() {
  amg.begin();
  stir.runMotor(100);
  //current sensor
  Serial.begin(9600);
    //for(int curThisReading=0; curThisReading < curNumReadings; curThisReading++) 
    //{
    //readings[curThisReading]=0;
    // }
}

void loop() {
  for (int i = 0; i < 30; i++) {
    
   // put your main code here, to run repeatedly:
  
  //current sensor
    //setting up updating array 
      //curTotal = curTotal - readings[curReadIndex]; //subtract the last reading
      //readings[curReadIndex] = ina.getFilteredCurrent(weight);
      unfilCurrent = ina.getUnfilteredCurrent();
      // curTotal = curTotal + readings[curReadIndex]; //add the reading to total
      // curReadIndex = curReadIndex + 1; //advance to the next position in the array
      
  
    //calculate the average
      //curAverage = curTotal/curNumReadings; 
  
    //end signal 
      // if (curAverage > currentThreshold) {
      //  currentEnd = 1;
      // }
      // perCurExceedThreshold = curAverage/currentThreshold; 
      
      // if(perCurExceedThreshold > 1.5){
      //  overirde = 1; 
      // }
    
  //IR camera 
    amg.readPixels(pixels);
    //implement a similar running average, but decide which pixels to samples 
    //end signal 
  
    //Print to serial monitor 
    Serial.print(unfilCurrent);
    Serial.print(",");
  
    for(int j = 0; j < 64 ; j++){
      Serial.print(pixels[j]);
      Serial.print(",");
    }
    Serial.println("");
    delay(500);
  }
  stir.reverseMotor();
  for (int i = 0; i < 10; i++) {
    delay(500);
  }
  stir.reverseMotor();
}
  
   

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
