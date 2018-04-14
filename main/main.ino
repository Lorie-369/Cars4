int motorLeft   = 5;
int motorRight  = 3;

int sensorLeft      = 10;
int sensorMid       = 9;
int sensorRight     = 8;
int sensorLeftMid   = 12;
int sensorLeftRight = 11;

int speedHigh = 255;
int speedMid  = 150;
int speedLow  = 80;

int lastRead[5] = {0, 0, 0, 0, 0};

// White 0
// Black 1

void setup() {
  Serial.begin(9600);
}

void loop() {
  int rLeft = 
}

void goForward() {
  digitalWrite(motorLeft, HIGH);
  digitalWrite(motorRight, HIGH);
}

void Stop() {
  digitalWrite(motorLeft, LOW);
  digitalWrite(motorRight, LOW);
}

void goLeft() {
  digitalWrite(motorLeft, HIGH);
  digitalWrite(motorRight, LOW);
}

void goRight() {
  digitalWrite(motorLeft, LOW);
  digitalWrite(motorRight, HIGH);
}

void writeHistory(int left, int mid, int right) {
  lastRead[0] = left;
  lastRead[1] = mid;
  lastRead[2] = right;
}

