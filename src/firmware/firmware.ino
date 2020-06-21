
#include <Arduino.h>
#include "RoombaSerial.h"
#include "msgs.h"

RoombaSerial rserial(9600);
// States:
// false: Inactive - no movement
// true: Active - commands being sent
bool activated = 0;
TwistMsg cmd_vel;

void setup() {
  rserial.init(); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  rserial.readSerial();
  rserial.checkHeartbeat(&activated);
  rserial.updateStatusLights(activated);

  if (activated) {
    rserial.updateCommand(&cmd_vel);
  } else {
    cmd_vel.linear = 0;
    cmd_vel.angular = 0;
  }

  Serial.println(cmd_vel);
}
