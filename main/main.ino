int leftMotor   = 5;
int rightMotor  = 3;

int leftSensor      = 10;
int midSensor       = 9;
int rightSensor     = 8;
int midLeftSensor   = 12;
int midRightSensor  = 11;

// Adjust the speed according to the motor.
int highSpeed = 140;
int normalSpeed  = 100;
int lowSpeed  = 0;

int onTrack = 1;
int offTrack = 0;

int history[5] = {0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
}

void loop() {
  int rLeft = digitalRead(leftSensor);
  int rMid = digitalRead(midSensor);
  int rRight = digitalRead(rightSensor);
  int rMidLeft = digitalRead(midLeftSensor);
  int rMidRight = digitalRead(midRightSensor);

  if (rMid == onTrack) {
      while (digitalRead(midSensor))
    goForward();
    rMid = 1;
  }

  else if (rMidLeft == onTrack) {
    while (digitalRead(midSensor) == offTrack) {
      goRight();
    }
    rMidRight = 1;
    goForward();
  }

  else if (rLeft == onTrack) {
    while (digitalRead(midSensor) == offTrack) {
      goFullRight();
    }
    rLeft = 1;
    goForward();
  }

  else if (rMidRight == onTrack) {
    while (digitalRead(midSensor) == offTrack) {
      goLeft();
    }
    rMidRight = 1;
    goForward();
  }

  else if (rRight == onTrack) {
    while (digitalRead(midSensor) == offTrack) {
      goFullLeft();
    }
    rRight = 1;
    goForward();
  }

  else {
    Stop();
  }

  writeHistory(rLeft, rMidLeft, 1, rMidRight, rRight);
}

void goForward() {
  analogWrite(leftMotor, highSpeed);
  analogWrite(rightMotor, highSpeed);
}

void Stop() {
  if (history[2] == onTrack) 
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
void writeHistory(int left, int midleft, int mid, int midright, int right) {
  history[0] = left;
  history[1] = midleft;
  history[2] = mid;
  history[3] = midright;
  history[4] = right;
}

