int leftMotor   = 5;
int rightMotor  = 3;

int leftSensor      = 10;
int sensorMid       = 9;
int rightSensor     = 8;
int midLeftSensor   = 12;
int midRightSensor  = 11;

int highSpeed = 255;
int normalSpeed  = 0;
int lowSpeed  = 0;

int onTrack = 1;
int offTrack = 0;

int history[5] = {0, 0, 0, 0, 0};

// White 0
// Black 1

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read sensors.
  // Left, Left<-Mid->Right, Right.
  int rLeft = digitalRead(leftSensor);
  int rMid = digitalRead(sensorMid);
  int rRight = digitalRead(rightSensor);
  int rMidLeft = digitalRead(midLeftSensor);
  int rMidRight = digitalRead(midRightSensor);

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
  // TODO:
  // Adjust the history to track all the sensors.	
  writeHistory(0, rMid, 0);
}

void goForward() {
  analogWrite(leftMotor, highSpeed);
  analogWrite(rightMotor, highSpeed);
}

void Stop() {
  // TODO:
  // Improve the history to track all the sensors [0...4], not just the mid sensor.
  // history[x]:
  //  0 – Left
  //  1 – Mid
  //  2 – Right
  if (history[1] == onTrack) 
    delay(1000);
  else
    // Adjust the delay, عشان عامل مشاكل. 
    delay(25);
    
  analogWrite(leftMotor, 0);
  analogWrite(rightMotor, 0);
}

// Hard turns.
void goFullLeft() {
  analogWrite(leftMotor, highSpeed);
  analogWrite(rightMotor, lowSpeed);
}

void goFullRight() {
  analogWrite(leftMotor, lowSpeed);
  analogWrite(rightMotor, highSpeed);
}

// Swift/light turns.
void goLeft() {
  analogWrite(leftMotor, highSpeed);
  analogWrite(rightMotor, normalSpeed);
}

void goRight() {
  analogWrite(leftMotor, normalSpeed);
  analogWrite(rightMotor, highSpeed);
}

// TODO:
// Expand the history capability to track all the sensors.
void writeHistory(int left, int mid, int right) {
  history[0] = left;
  history[1] = mid;
  history[2] = right;
}

