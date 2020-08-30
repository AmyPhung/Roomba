#include <SoftwareSerial.h>
int rxPin=3;
int txPin=4;
int ddPin=5; //device detect
int sensorbytes[4]; //array to store encoder counts
int angle;
//const float PI=3.1415926;
#define left_encoder (sensorbytes[0])
#define right_encoder (sensorbytes[1])
#define clamp(value, min, max) (value < min ? min : value > max ? max : value)
SoftwareSerial Roomba(rxPin,txPin);
//
//void twistDrive(int linear, int angular) {
///*  
// *   linear velocity: m/s
// *   angular velocity: rad/s
// *   TODO: Handle edge cases (for fast speeds or large radii)
// */
// int velocity, radius;
// 
// if (angular == 0) { //straight
//   radius = 32767;
// } else if (linear == 0 && angular == -1) { //turn in place CW
//   radius = -1;
// } else if (angular == 1) { //turn in place CCW
//   radius = 1;
// } else {
//   radius = linear / angular;
// }
//  
//}
//
//void radDrive(int velocity, int radius) {
///*  
// *   Drive command in Roomba-friendly units
// *   velocity: mm/s
// *   radius: mm
// */
//  
//  clamp(velocity, -500, 500); //cap max and min velocity in mm/s
//  clamp(radius, -2000, 2000); //cap max and min radius in mm (positive is left)
//  
//  Roomba.write(137);
//  Roomba.write(velocity >> 8);
//  Roomba.write(velocity);
//  Roomba.write(radius >> 8);
//  Roomba.write(radius);
//}

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
//  updateSensors();

//  // Spin slowly
//  Roomba.write(byte(145));
//  Roomba.write(byte(0x00));
//  Roomba.write(byte(0x0B));
//  Roomba.write(byte(0xFF));
//  Roomba.write(byte(0xF5));  

  int velocity = 100;

  // Move wheels opposite each other
  Roomba.write(byte(145));
  Roomba.write(velocity >> 8);
  Roomba.write(velocity);
  Roomba.write(-velocity >> 8);
  Roomba.write(-velocity);  

//  float speed_wish_right = (cmd_vel.angle*WHEEL_DIST)/2 + cmd_vel.speed;
//float speed_wish_left = cmd_vel.speed*2-speed_wish_right;


//  testdrive(100, 2000);
}

void loop() {
//    Serial.println("updating sensors...");
//    updateSensors();
//    // stop if angle is greater than 360 degrees
//    if(abs(angle)>2*pi){
//      Roomba.write(173);
    delay(100);
//    }
}

void updateSensors() {
  // call for the left and right encoder counts
  Roomba.write(byte(148));
  Roomba.write(byte(2));
  Roomba.write(byte(43));
  Roomba.write(byte(44));
  delay(100);

  // load encoder counts into an array
  int i = 0;
  while(Roomba.available()) {
    Serial.println("reading...");
    int c = Roomba.read();
    sensorbytes[i] = c;
    i++;
    Serial.println(c);
  }
//  angle=((right_encoder*72*pi/508.8)-(left_encoder*72*pi/508.8))/235;
//  Serial.println(angle);
}
