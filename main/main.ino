int motorLeft   = 5;
int motorRight  = 3;

int sensorLeft      = 10;
int sensorMid       = 9;
int sensorRight     = 8;
int sensorMidLeft   = 12;
int sensorMidRight  = 11;

int speedHigh = 255;
int speedMid  = 0;
int speedLow  = 0;

int onTrack = 1;
int offTrack = 0;

int lastRead[5] = {0, 0, 0, 0, 0};

// White 0
// Black 1

void setup() {
  Serial.begin(9600);
}

void loop() {
  int rLeft = digitalRead(sensorLeft);
  int rMid = digitalRead(sensorMid);
  int rRight = digitalRead(sensorRight);
  int rMidLeft = digitalRead(sensorMidLeft);
  int rMidRight = digitalRead(sensorMidRight);

  if (rMid == onTrack) {
    goForward();
  } else if (rMidLeft == onTrack) {
    goRight();
  } else if (rLeft == onTrack) {
    goFullRight();
  } else if (rMidRight == onTrack) {
    goLeft();
  } else if (rRight == onTrack) {
    goFullLeft();
  } else {
    Stop();
  }

  writeHistory(0, rMid, 0);
}

void goForward() {
  analogWrite(motorLeft, speedHigh);
  analogWrite(motorRight, speedHigh);
}

void Stop() {
  // lastRead [0...4] not just the mid sensor
  if (lastRead[1] == onTrack) 
    delay(1000);
  else 
    delay(25);
    
  analogWrite(motorLeft, 0);
  analogWrite(motorRight, 0);
}

void goFullLeft() {
  analogWrite(motorLeft, speedHigh);
  analogWrite(motorRight, speedLow);
}

void goFullRight() {
  analogWrite(motorLeft, speedLow);
  analogWrite(motorRight, speedHigh);
}

void goLeft() {
  analogWrite(motorLeft, speedHigh);
  analogWrite(motorRight, speedMid);
}

void goRight() {
  analogWrite(motorLeft, speedMid);
  analogWrite(motorRight, speedHigh);
}

void writeHistory(int left, int mid, int right) {
  lastRead[0] = left;
  lastRead[1] = mid;
  lastRead[2] = right;
}

