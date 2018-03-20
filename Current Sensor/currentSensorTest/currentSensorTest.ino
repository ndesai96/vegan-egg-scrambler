int value;
int offset = 510;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);   // unsure what 9600 does 
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(A0)-offset;
  Serial.print(value);
  Serial.print("\n");

}
