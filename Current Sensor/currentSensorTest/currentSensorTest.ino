int analogPin = 0;
double raw_value;
double current;
double offset = 511.0;
int motorPin = 3;
double currentSum = 0.0;
int runningAvgCt = 10;
double runningAvg;
double speed = .5*255; //% of total speed

void setup() {

  // start serial output
  pinMode(motorPin,OUTPUT);
  Serial.begin(9600); // baud rate of 9600
}

void loop() {
  //start motor 
  
  if(speed >=0&&speed<=255);
    analogWrite(motorPin,speed);
  for (int i = 0; i < runningAvgCt; i++){
    // read and adjust raw value reading from sensor
    raw_value = analogRead(analogPin) - offset;
    current = (raw_value*.0727) + 0.0195;
//    Serial.println(current);
    currentSum = currentSum + current;
    delay(100);
  }
  runningAvg = currentSum / runningAvgCt;
  Serial.println(runningAvg);
  currentSum=0;
  
  
   //code current stop
  if( abs(current)>2.5) { 
    speed=0;
  }
  else {
    speed=.5*255;
  }
    

  // print results to serial monitor
  


 
}
