#include "Roomba.h"

Roomba::Roomba(SoftwareSerial * serial)
{
  RoombaSerial = serial;
}

void Roomba::init()
{
  Serial.begin(115200);
  RoombaSerial->begin(115200);
  Serial.println ("Sending start command...");
  delay (1000);
   // set up ROI to receive commands
  RoombaSerial->write(128);  // START
  delay(150);
  Serial.println ("Sending Safe Mode command...");
  delay (1000);
  RoombaSerial->write(131);  // CONTROL
  delay(150);
  Serial.println ("Ready to go!");
  delay (5000);
}

void Roomba::move(int velocity, int radius)
{
  RoombaSerial->write(137);
  RoombaSerial->write((velocity & 0xff00) >> 8);
  RoombaSerial->write(velocity & 0xff);
  RoombaSerial->write((radius & 0xff00) >> 8);
  RoombaSerial->write(radius & 0xff);
}
