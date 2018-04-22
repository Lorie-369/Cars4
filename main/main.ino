int leftMotor  = 5;
int rightMotor = 3;

int leftSensor     = 10;
int midLeftSensor  = 12;
int midSensor      = 9;
int midRightSensor = 11;
int rightSensor    = 8;

// Adjust the speed according to the motor.
int highSpeed   = 200;
int normalSpeed = 140;
int lowSpeed    = 0;

int onTrack  = 1;
int offTrack = 0;

int history[5] = {0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
}

int blank() {
  int rLeft     = digitalRead(leftSensor);
  int rMid      = digitalRead(midSensor);
  int rRight    = digitalRead(rightSensor);
  int rMidLeft  = digitalRead(midLeftSensor);
  int rMidRight = digitalRead(midRightSensor);

  if (rLeft     == offTrack && 
      rMid      == offTrack &&
      rRight    == offTrack &&
      rMidLeft  == offTrack && 
      rMidRight == offTrack)
    return 1;
  else
    return 0;
}

void loop() {
  int rLeft     = digitalRead(leftSensor);
  int rMid      = digitalRead(midSensor);
  int rRight    = digitalRead(rightSensor);
  int rMidLeft  = digitalRead(midLeftSensor);
  int rMidRight = digitalRead(midRightSensor);

  // while (blank() == 1)
  //   goForward();

  if (rMid == onTrack) {
    while (digitalRead(midSensor) && blank() == 0)
      goForward();
    rMid = 1;
  }

  else if (rMidLeft == onTrack) {
    while (digitalRead(midSensor) == offTrack && blank() == 0) {
      goRight();
    }
    rMidRight = 1;
    rMid = 1;
  }

  else if (rLeft == onTrack) {
    while (digitalRead(midSensor) == offTrack && blank() == 0) {
      goFullRight();
    }
    rLeft = 1;
    rMid = 1;
  }

  else if (rMidRight == onTrack) {
    while (digitalRead(midSensor) == offTrack && blank() == 0) {
      goLeft();
    }
    rMidRight = 1;
    rMid = 1;
  }

  else if (rRight == onTrack) {
    while (digitalRead(midSensor) == offTrack && blank() == 0) {
      goFullLeft();
    }
    rRight = 1;
    rMid = 1;
  }

  else {
    Stop();
  }

  writeHistory(rLeft, rMidLeft, rMid, rMidRight, rRight);
}

void goForward() {
  analogWrite(leftMotor, highSpeed);
  analogWrite(rightMotor, highSpeed);
}

void Stop() {
  if (history[2] == onTrack) {
    delay(1000);
  }

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

void writeHistory(int left, int midleft, int mid, int midright, int right) {
  history[0] = left;
  history[1] = midleft;
  history[2] = mid;
  history[3] = midright;
  history[4] = right;
}