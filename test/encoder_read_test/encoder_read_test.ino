#include <SoftwareSerial.h>
int rxPin=3;
int txPin=4;
int ddPin=5; //device detect
int sensorbytes[4]; //array to store encoder counts
int angle;
const float pi=3.1415926;
#define left_encoder (sensorbytes[0])
#define right_encoder (sensorbytes[1])
#define clamp(value, min, max) (value < min ? min : value > max ? max : value)
SoftwareSerial Roomba(rxPin,txPin);

void testdrive(int velocity, int radius)
{
  clamp(velocity, -500, 500); //def max and min velocity in mm/s
  clamp(radius, -2000, 2000); //def max and min radius in mm (positive is left)
  
  Roomba.write(137);
  Roomba.write(velocity >> 8);
  Roomba.write(velocity);
  Roomba.write(radius >> 8);
  Roomba.write(radius);
}

void setup() {
  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
//  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Roomba.begin(19200);

  // wake up the robot
  digitalWrite(ddPin, HIGH);
  delay(100);
  digitalWrite(ddPin, LOW);
  delay(500);
  digitalWrite(ddPin, HIGH);
  delay(2000);

  Roomba.write(byte(128));  //Start
  Roomba.write(byte(131));  //Safe mode
  updateSensors();

//  // Spin slowly
//  Roomba.write(byte(145));
//  Roomba.write(byte(0x00));
//  Roomba.write(byte(0x0B));
//  Roomba.write(byte(0xFF));
//  Roomba.write(byte(0xF5));  
//  testdrive(100, 2000);
}

void loop() {
    Serial.println("updating sensors...");
    updateSensors();
    // stop if angle is greater than 360 degrees
//    if(abs(angle)>2*pi){
//      Roomba.write(173);
//      delay(100);
//    }
}


void updateSensors() {
  // call for the left and right encoder counts
  Roomba.write(byte(142));
////  Roomba.write(byte(2));
  Roomba.write(byte(43));
//  Roomba.write(byte(44));
  delay(100);

  // load encoder counts into an array
  int i = 0;
  while(Roomba.available()) {
//    Serial.println("reading...");
    int c = Roomba.read();
//    sensorbytes[i] = c;
//    i++;
    
    delay(100);
    if (c != 19) {
      Serial.println(c);
    } else{
      Serial.println("---");
    }
  }
//  delay(1000000);
//  angle=((right_encoder*72*pi/508.8)-(left_encoder*72*pi/508.8))/235;
//  Serial.println(angle);
}
