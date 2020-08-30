int incoming_byte = 0; // for incoming serial data
int ser_buf[20];

struct twistCmd {
  int linear;
  int angular;
};


twistCmd cmd_vel;

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

void parseInput(int *buf, twistCmd *cmd) {
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
  }

}

int arrSize;

void setup() {
  Serial.begin(115200);
}
void loop() {

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
  }
}
