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

void Roomba::twistMove(int linear, int angular) {
  clamp(linear, -500, 500); //cap max and min velocity in m/s * 1000
  clamp(angular, -4000, 4000); //cap max and min velocity in rad/s * 1000

  float f_lin = (float)linear/1000.0;
  float f_ang = (float)angular/1000.0;

  // Compute wheel commands and rescale from meters to mm
  int rcmd = (f_lin + (f_ang*WHEEL_DIST)/2) * 1000;
  int lcmd  = (f_lin - (f_ang*WHEEL_DIST)/2) * 1000;
  rcmd = clamp(rcmd, -500, 500); //cap max and min velocity in mm/s
  lcmd = clamp(lcmd, -500, 500); //cap max and min velocity in mm/s

  wheelMove(lcmd, rcmd);
}

void Roomba::updateSensors() {
  RoombaSerial->write(byte(149)); // Query list
  RoombaSerial->write(byte(2));   // Request 2 packets
  RoombaSerial->write(byte(43));  // Left encoder counts
  RoombaSerial->write(byte(44));  // Right encoder counts
  delay(100); // wait for sensors
  int i=0;

  char sensorbytes[100];

  while(RoombaSerial->available()) {
    // read values into signed char array
    sensorbytes[i++] = RoombaSerial->read();
  }

  // merge upper and lower bytes
  r_enc = (int)(sensorbytes[2] << 8)|(int)(sensorbytes[3]&0xFF);
  l_enc  = (int)(sensorbytes[0] << 8)|(int)(sensorbytes[1]&0xFF);
}
