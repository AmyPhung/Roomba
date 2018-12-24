#include "Roomba.h"

#define rx 10
#define tx 11

// Roomba Variables
SoftwareSerial ss(rx,tx);
Roomba myRoomba(&ss);

// Operator Input Variables
String command = "32";            //operator command string - 32 is cmd for stop (spacebar)

// Real Time Loop Variables
boolean realTimeRun = true;          //real time control loop flag
unsigned long oldLoopTime = 0;       //past loop time in milliseconds
unsigned long newLoopTime = 0;       //new loop time in milliseconds
unsigned long cycleTime = 0;         //elapsed loop cycle time
const long controlLoopInterval = 50; //control loop cycle time in milliseconds


void setup() {
  Serial.begin(115200);
  myRoomba.init();
}
void loop() {
  Serial.println("Input Command");
  command = getOperatorInput();

  if (command == "10") {
    Serial.println("Ignoring carriage return");
    command = getOperatorInput();
  }
  if (command == "32") {
    Serial.println("Stopped");
    myRoomba.move(0,0);
    realTimeRun = false;
  }
  else {
    Serial.println("Command entered!");
    realTimeRun = true;
    Serial.read(); // Clear carriage return
  }

  while (realTimeRun == true) {       // if OCU-Stop not commanded, run control loop
    if (checkOperatorInput() == 1) {
      break;
    }

    // ------------------------------- REAL TIME LOOP CONTROL STARTS HERE ------------------
    if (newLoopTime - oldLoopTime >= controlLoopInterval) { // if true run flight code
      oldLoopTime = newLoopTime;          // reset time stamp

      classifyCommand(command);
      Serial.println("loop");
    }
    // ----------------------------- REAL TIME CONTROL LOOP ENDS HERE --------------------
  }
}





String getOperatorInput()
{
  while (Serial.available() == 0) {}; // do nothing until operator input typed
  command = Serial.read();      // read command string
  return command;
}

int checkOperatorInput() {
  // Check if operator inputs a command during real-time loop execution
  if (Serial.available() > 0) {         // check to see if operator typed at OCU
    realTimeRun = false;            // if OCU input typed, stop control loop
    command = Serial.read();
    Serial.read(); // Clear carriage return
    return 1;                              // break out of real-time loop
  }
  else {
    realTimeRun = true; // if no operator input, run real-time loop
  }

  // Real-Time clock control. Check to see if one clock cycle has elapesed before running this control code
  newLoopTime = millis();               // get current Arduino time (50 days till wrap)
  return 0;
}

int classifyCommand(String command) {
  // Since command is a string, we compare it to the ASCII code, not the int value
  // e.g. ASCII for "1" is 49
  if (command == "48") { //0
    return 0; // run mission
  }
  else if (command == "49") { //1
    return 1; // stopped
  }
  else if (command == "50") { //2
    return 2; // undock on left
  }
  else if (command == "51") { //3
    return 3; // undock on right
  }
  else if (command == "52") { //4
    return 4; // left wall follow
  }
  else if (command == "53") { //5
    return 5; // right wall follow
  }
  else if (command == "54") { //6
    return 6; // left circle
  }
  else if (command == "55") { //7
    return 7; // right circle
  }
  else if (command == "56") { //8
    return 8; //chase
  }
  else if (command == "57") { //9
    return 9; // search
  }

  // TELEOPERATED CONTROL
  else if (command == "119") { // Keypress: W
    myRoomba.move(100,0);
    return 10;
  }
  else if (command == "97") { // Keypress: A
    myRoomba.move(100,1);
    return 11;
  }
  else if (command == "115") { // Keypress: S
    myRoomba.move(-100,0);
    return 12;
  }
  else if (command == "100") { // Keypress: D
    myRoomba.move(100,-1);
    return 13;
  }
  else {
    return 1;
  }
}
