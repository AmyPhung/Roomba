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

void Roomba::updateSensors() {
  RoombaSerial->write(byte(149)); // request encoder counts
  RoombaSerial->write(byte(2));
  RoombaSerial->write(byte(43));
  RoombaSerial->write(byte(44));
  delay(100); // wait for sensors
  int i=0;

  char sensorbytes[100];
  int right_encoder;
  int left_encoder;
  float angle;

  while(RoombaSerial->available()) {
    sensorbytes[i++] = RoombaSerial->read();  //read values into signed char array
  }

  //merge upper and lower bytes
  right_encoder=(int)(sensorbytes[2] << 8)|(int)(sensorbytes[3]&0xFF);
  left_encoder=int((sensorbytes[0] << 8))|(int(sensorbytes[1])&0xFF);

  angle=((right_encoder*72*3.14/508.8)-(left_encoder*72*3.14/508.8))/235;
  Serial.println (angle);
}
