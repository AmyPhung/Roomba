#ifndef Roomba_h
#define Roomba_h

#include <Arduino.h>
#include <SoftwareSerial.h>

class Roomba
{
  public:
    Roomba(SoftwareSerial * ss);
    void init();
    void move(int velocity, int radius); // Velocity goes from -500 to 500, radius goes from -2000 to 2000
    void updateSensors();
  private:
    SoftwareSerial * RoombaSerial;
};


// #define bumpright (sensorbytes[0] & 0x01)
// #define bumpleft  (sensorbytes[0] & 0x02)

#endif
