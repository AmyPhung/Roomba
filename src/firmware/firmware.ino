
#include <Arduino.h>
#include "RoombaSerial.h"
#include "Roomba.h"
#include "msgs.h"

// For Roomba communications
int rxPin=3;
int txPin=4;
int ddPin=5; //device detect
int sensor_update_rate = 1000; //in ms

SoftwareSerial rSerial(rxPin,txPin);
Roomba myRoomba(&rSerial);

//RoombaSerial rserial(9600);
//// States:
//// false: Inactive - no movement
//// true: Active - commands being sent
//bool activated = 0;
TwistMsg cmd_vel;

int incoming_byte = 0; // for incoming serial data
int ser_buf[20];
int arrSize;
int last_sensor_update;

void readInput(int *buf) {
  int i = 0;

  // Save all chars until E is found
  do {
    if (Serial.available() > 0) {
      incoming_byte = Serial.read();
      buf[i] = incoming_byte;
      i++;
    }
  } while (incoming_byte != 69);
}

void parseInput(int *buf, TwistMsg *cmd) {
  // Parse serial input from Python and convert to twistCmd
  // Data example 1: SL+100A+100E
  // Data example 2: SL-45A+30E

  // S = 83
  // L = 76
  // A = 65
  // E = 69
  // + = 43
  // - = 45
  // CR = 10

  // 0 = 48
  // 1 = 49
  // 2 = 50
  //  ...

  Serial.println("parsing input...");
  int i = 0;
  int lsign = 1;
  int asign = 1;
  int linear = 0;
  int angular = 0;

  // Find an L to start reading linear cmd
  if (buf[i] == 76) {
    i++;

    // Update sign of linear cmd
    if (buf[i] == 45) lsign = -1;
    i++;

    // Update linear value until an A is found
    do {
      linear = linear*10 + (buf[i]-48);
      i++;
    } while (buf[i] != 65);
    i++;

   // Update sign of angular cmd
    if (buf[i] == 45) asign = -1;
    i++;

    // Update angular value until an E is found
    do {
      angular = angular*10 + (buf[i]-48);
      i++;
    } while (buf[i] != 69);


    Serial.println("Linear value:");
    Serial.println(lsign * linear);
    Serial.println("Angular value:");
    Serial.println(asign * angular);

    cmd_vel.linear = (lsign * linear);
    cmd_vel.angular = (asign * angular);
  }
}

bool isValid(int linear, int angular) {
  if (abs(linear) > 500) return false;
  if (abs(angular) > 4000) return false;
  return true;
}

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

  // Reset timers
  last_sensor_update = millis();

//  myRoomba.wheelMove(100,0);
//  myRoomba.twistMove(0.2, 1);
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

  // Update sensors at regular interval
  if ((millis() - last_sensor_update) > sensor_update_rate) {
    myRoomba.updateSensors();
    Serial.print("L_ENC");
    Serial.println(myRoomba.l_enc);
    Serial.print("R_ENC");
    Serial.println(myRoomba.r_enc);
  }

  // If new command is found (starting with S)
  if ((Serial.available() > 0) && (Serial.read() == 83)) {
    Serial.println("reading...");
    readInput(ser_buf);

    // For debugging ----
    arrSize = *(&ser_buf + 1) - ser_buf;
    for (int i=0; i<arrSize; i++) {
      Serial.print(ser_buf[i]);
      Serial.print(" ");
    }
    Serial.println(" ");
    // ------------------

    parseInput(ser_buf, &cmd_vel);
    if (isValid(cmd_vel.linear, cmd_vel.angular)) {
      myRoomba.twistMove(cmd_vel.linear, cmd_vel.angular);
    }
  }
}
