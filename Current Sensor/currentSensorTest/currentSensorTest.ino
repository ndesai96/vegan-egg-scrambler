// USER INPUT

const int analogPin = 0; // analog pin used for current sensor
const int motorPin = 3; // digital pin for motor

int runningAvgCt = 10; // number of values considered in average current calculation
int delayTime = 100; // time between loops in milliseconds

float desiredSpeedPercent = 50; // duty cycle percentage (PWM)

// variable/constant/default initialization;

int raw_value; // container for analogRead value with offset
const float raw_offset = 511.0; // experimentally determined DC offset for current sensor
const float cal_m = 0.727; // calibration coefficient
const float cal_b = 0.0195; // calibration offset

float current; // container for current value
float runningAvg; // container for the averaged current
float currentSum = 0.0; // container for sum of current values
float motorSpeed = 0.0; // container for motor speed output

void setup() {

  // start serial output
  pinMode(motorPin,OUTPUT);
  Serial.begin(9600); // baud rate of 9600
}

void loop() {
  //start motor 
  
  if(motorSpeed>=0 && motorSpeed<=255) {
    analogWrite(motorPin,motorSpeed);
    for (int i = 0; i < runningAvgCt; i++){
      // read and adjust raw value reading from sensor
      raw_value = analogRead(analogPin) - raw_offset;
      current = (raw_value*cal_m) + cal_b;
      currentSum = currentSum + current;
      delay(100);
    }
    runningAvg = currentSum / runningAvgCt;
    Serial.println(runningAvg);
    currentSum=0;
  }
   //code current stop
  if( abs(current)>2.5) { 
    motorSpeed=0;
  }
  else {
    motorSpeed=desiredSpeedPercent*255/100;
  } 
}
