int rxPin = 0;
int txPin = 1;
int ddPin = 2;


void setup() {
  pinMode(txPin,  OUTPUT);
  pinMode(ddPin,  OUTPUT); 
  Serial.begin(19200);


  digitalWrite(ddPin, HIGH);
  delay(100);
  digitalWrite(ddPin, LOW);
  delay(500);
  digitalWrite(ddPin, HIGH);
  delay(2000);
  Serial.write(128); 
  delay(50);
  Serial.write(130); 

}

void loop() {
  
  spinL();

}

void spinL() {
  Serial.write(137); 
  Serial.write(0x00);  
  Serial.write(0xc8);
  Serial.write(0x00);
  Serial.write(0x01);   
}
