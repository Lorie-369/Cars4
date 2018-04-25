int leftMotor   = 5;
int rightMotor  = 3;

int leftSensor      = 10;
int midSensor       = 9;
int rightSensor     = 8;
int midLeftSensor   = 12;
int midRightSensor  = 11;

int highSpeed = 200;
int normalSpeed  = 0;
int lowSpeed  = 0;

int onTrack = 1;
int offTrack = 0;

int history[5] = {0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
}

// Check for blank spot

bool blank() {

  // Read the sensors' data

  int rLeft = digitalRead(leftSensor);
  int rMid = digitalRead(midSensor);
  int rRight = digitalRead(rightSensor);
  int rMidLeft = digitalRead(midLeftSensor);
  int rMidRight = digitalRead(midRightSensor);

  // If they're all off the track, return 1 (true), else, return 0 (false).

  if (rLeft == offTrack &&
    rMid == offTrack &&
    rRight == offTrack &&
    rMidLeft == offTrack &&
    rMidRight == offTrack)
    return 1;
  else 
    return 0;
}

// Check for more than one sensor on track

bool moreThanOne() {
  int rLeft = digitalRead(leftSensor);
  int rMid = digitalRead(midSensor);
  int rRight = digitalRead(rightSensor);
  int rMidLeft = digitalRead(midLeftSensor);
  int rMidRight = digitalRead(midRightSensor);

  // At least one of five, 1/5 = 0.2, return 1 (true) if true, else return 0 (false)

  if ((rLeft + rMid + rRight + rMidLeft + rMidRight) / 5 > 0.2)
    return 1;
  else
    return 0;
}

void loop() {

  // If the mid sensor is on track, keep moving forward till it gets
  // off the track

  if (digitalRead(midSensor) == onTrack) {
    while (digitalRead(midSensor) == onTrack)
      goForward();

    // If the mid left sensor is on track, keep moving forward till the 
    // mid sensor gets on the track.
    // 
    // Break the while loop when blank spot is detected, or more than a
    // sensor is on the track.

  } else if (digitalRead(midLeftSensor) == onTrack) {
    while (digitalRead(midSensor) == offTrack && blank() == 0 && moreThanOne() == 0)
      goRight();

  } else if (digitalRead(leftSensor) == onTrack) {
    while (digitalRead(midLeftSensor) == offTrack && blank() == 0 && moreThanOne() == 0)
      goFullRight();

  } else if (digitalRead(midRightSensor) == onTrack) {
    while (digitalRead(midSensor) == offTrack && blank() == 0 && moreThanOne() == 0)
      goLeft();

  } else if (digitalRead(rightSensor) == onTrack) {
    while (digitalRead(midRightSensor) == offTrack && blank() == 0 && moreThanOne() == 0)
      goFullLeft();
  }

  // At the end, stop.
  // This won't affect the process, while the sensors are on track.

  Stop();
}

void goForward() {
  analogWrite(leftMotor, highSpeed);
  analogWrite(rightMotor, highSpeed);
}

void Stop() {
  delay(30);
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