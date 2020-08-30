
#include <Arduino.h>
#include "RoombaSerial.h"
#include "Roomba.h"
#include "msgs.h"

// For Roomba communications
int rxPin=3;
int txPin=4;
int ddPin=5; //device detect

SoftwareSerial rSerial(rxPin,txPin);
Roomba myRoomba(&rSerial);

//RoombaSerial rserial(9600);
//// States:
//// false: Inactive - no movement
//// true: Active - commands being sent
//bool activated = 0;
TwistMsg cmd_vel;

void setup() {
  // Set pin modes
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  pinMode(ddPin, OUTPUT);

  // Open serial monitor for debugging
  Serial.begin(115200);
  // Start Roomba serial
  rSerial.begin(19200);

  // wake up the robot
  digitalWrite(ddPin, HIGH);
  delay(100);
  digitalWrite(ddPin, LOW);
  delay(500);
  digitalWrite(ddPin, HIGH);
  delay(2000);

  // Initialize Roomba
  myRoomba.init();
//  myRoomba.wheelMove(100,0);
  myRoomba.twistMove(0.2, 1);
}

void loop() {
//  myRoomba.readSerial();/
//  myRoomba.checkHeartbeat(&activated);
//  myRoomba.updateStatusLights(activated);

//  if (activated) {
  
//  Serial.println(cmd_vel);/
  
//  myRoomba.move(cmd_vel.linear, cmd_vel.angular);
//  } else {
//    cmd_vel.linear = 0;
//    cmd_vel.angular = 0;
//  }

  
}
