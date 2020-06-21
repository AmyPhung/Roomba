#ifndef RoombaSerial_h
#define RoombaSerial_h

#include <Arduino.h>
#include "msgs.h"

class RoombaSerial{
  public:
    RoombaSerial(int baud);
    void init();
    void readSerial();
    void checkHeartbeat(bool *active);
    void updateStatusLights(bool active);
    void updateCommand(TwistMsg *cmd);
    
    // Minimum heartbeat frequency (in ms)
    // Default: 1 second
    int timeout = 1000;

  private:
    int baud_rate;

    unsigned long last_heartbeat;
    unsigned long last_blink;
    
    // for incoming serial data
    int incoming_byte = 0;
    int ser_buf[20];
  
};

#endif
