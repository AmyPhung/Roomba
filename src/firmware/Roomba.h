#ifndef Roomba_h
#define Roomba_h

#include <Arduino.h>
#include <SoftwareSerial.h>

#define WHEEL_DIST 0.234

class Roomba {
  public:
    Roomba(SoftwareSerial * ss);
    void init();
    void radMove(int velocity, int radius); // Velocity goes from -500 to 500 (mm/s), radius goes from -2000 to 2000 (mm)
    void wheelMove(int lcmd, int rcmd); // Velocity for each wheel goes from -500 to 500 (mm/s)
    void twistMove(int linear, int angular); // Linear in units of m/s*1000, angular in radians*1000

    void updateSensors();
    int l_enc; // Left encoder readings in millimeters
    int r_enc; // Right encoder readings in millimeters
  private:
    SoftwareSerial * RoombaSerial;
};


// #define bumpright (sensorbytes[0] & 0x01)
// #define bumpleft  (sensorbytes[0] & 0x02)

#endif
