#include "Roomba.h"

#define clamp(value, min, max) (value < min ? min : value > max ? max : value)

Roomba::Roomba(SoftwareSerial * serial) {
  RoombaSerial = serial;
}

void Roomba::init() {
  Serial.println ("Sending start command...");
  RoombaSerial->write(128);  // START
  Serial.println ("Sending Safe Mode command...");
  RoombaSerial->write(131);  // SAFE MODE
  Serial.println ("Ready to go!");
}

void Roomba::radMove(int velocity, int radius) {
  clamp(velocity, -500, 500); //cap max and min velocity in mm/s
  clamp(radius, -2000, 2000); //cap max and min radius in mm (positive is left)
  
  RoombaSerial->write(137);
  RoombaSerial->write((velocity & 0xff00) >> 8);
  RoombaSerial->write(velocity & 0xff);
  RoombaSerial->write((radius & 0xff00) >> 8);
  RoombaSerial->write(radius & 0xff);
}

void Roomba::wheelMove(int lcmd, int rcmd) {
  clamp(lcmd, -500, 500); //cap max and min velocity in mm/s
  clamp(rcmd, -500, 500); //cap max and min velocity in mm/s
  
  RoombaSerial->write(byte(145));
  RoombaSerial->write(rcmd >> 8);
  RoombaSerial->write(rcmd);
  RoombaSerial->write(lcmd >> 8);
  RoombaSerial->write(lcmd);  
}

void Roomba::twistMove(float linear, float angular) {
  clamp(linear, -0.5, 0.5); //cap max and min velocity in m/s
  clamp(angular, -4, 4); //cap max and min velocity in rad/s

  // Compute wheel commands and rescale from meters to mm
  int rcmd = (linear + (angular*WHEEL_DIST)/2) * 1000;
  int lcmd  = (linear - (angular*WHEEL_DIST)/2) * 1000;
  rcmd = clamp(rcmd, -500, 500); //cap max and min velocity in mm/s
  lcmd = clamp(lcmd, -500, 500); //cap max and min velocity in mm/s
  wheelMove(lcmd, rcmd);
}





//
//void Roomba::updateSensors() {
//  RoombaSerial->write(byte(149)); // request encoder counts
//  RoombaSerial->write(byte(2));
//  RoombaSerial->write(byte(43));
//  RoombaSerial->write(byte(44));
//  delay(100); // wait for sensors
//  int i=0;
//
//  char sensorbytes[100];
//  int right_encoder;
//  int left_encoder;
//  float angle;
//
//  while(RoombaSerial->available()) {
//    sensorbytes[i++] = RoombaSerial->read();  //read values into signed char array
//  }
//
//  //merge upper and lower bytes
//  right_encoder=(int)(sensorbytes[2] << 8)|(int)(sensorbytes[3]&0xFF);
//  left_encoder=int((sensorbytes[0] << 8))|(int(sensorbytes[1])&0xFF);
//
//  angle=((right_encoder*72*3.14/508.8)-(left_encoder*72*3.14/508.8))/235;
//  Serial.println (angle);
//}
