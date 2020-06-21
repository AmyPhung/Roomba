/*
 * Data example 1: SL+100A+100E  
 * Data example 2: SL-45A+30E

  // S = 83 (start cmd message)
  // L = 76 (linear velocity)
  // A = 65 (angular velocity)
  // E = 69 (end cmd message)
  // + = 43
  // - = 45
  // CR = 10
  
  // 0 = 48
  // 1 = 49
  // 2 = 50
  //  ...

  H = 72 (heartbeat)
 */


#include "RoombaSerial.h"

RoombaSerial::RoombaSerial(int baud)
{
  baud_rate = baud;
}

void RoombaSerial::init()
{
  Serial.begin(baud_rate);
  last_heartbeat = millis();
  pinMode(LED_BUILTIN, OUTPUT);
}


void RoombaSerial::readSerial() {
  if ((Serial.available() > 0) && (Serial.read() == 83)) {
    int arrSize = *(&ser_buf + 1) - ser_buf;

    // Reset serial buffer
//    std::fill(ser_buf, ser_buf+arrSize, 0);

    // Start counter
    int i = 0;
    
    // Save all chars until end character (E) is found
    do {
      if (Serial.available() > 0) {
        incoming_byte = Serial.read();
        ser_buf[i] = incoming_byte;
        i++;
      }
    } while (incoming_byte != 69);

  
    // TODO: Parse serial here
  
//    // Print output 
//    for (int i=0; i<arrSize; i++){
//      Serial.print(ser_buf[i]);
//      Serial.print(" ");
//    }
//    Serial.println();
  }
}

void RoombaSerial::checkHeartbeat(bool *active) {
  // Check if new heartbeat was recieved
  if ((Serial.available() > 0) && (Serial.read() == 72)) {
    last_heartbeat = millis();
    *active = 1;
  }

  // Check if heartbeat has been recieved recently
  if ((millis() - last_heartbeat) > timeout) {
    *active = 0; // Disactivate robot if it's been too long
  }
}

void RoombaSerial::updateStatusLights(bool active) {
  if (!active) {
    // Solid light for inactive
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    // Blinking light for active
    if (millis() - last_blink > 200) {
      // If it's been awhile, initiate the blink
      digitalWrite(LED_BUILTIN, HIGH);
      last_blink = millis();
    } else if (millis() - last_blink < 100) {
      // Keep the blink on for a bit
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }
    
  }
}

void RoombaSerial::updateCommand(TwistMsg *cmd) {
  if (ser_buf[0] != 76) {
    // If start of serial buffer doesn't look right, stop robot
    cmd->linear = 0;
    cmd->angular = 0;
  } else {
    // TODO:
    cmd->linear = 100;
    cmd->angular = 100;    
  }
}
