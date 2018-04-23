int leftMotor   = 5;
int rightMotor  = 3;

int leftSensor      = 10;
int midSensor       = 9;
int rightSensor     = 8;
int midLeftSensor   = 12;
int midRightSensor  = 11;

int highSpeed = 120;
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

bool blank() {
  int rLeft = digitalRead(leftSensor);
  int rMid = digitalRead(midSensor);
  int rRight = digitalRead(rightSensor);
  int rMidLeft = digitalRead(midLeftSensor);
  int rMidRight = digitalRead(midRightSensor);

  if (rLeft == offTrack &&
    rMid == offTrack &&
    rRight == offTrack &&
    rMidLeft == offTrack &&
    rMidRight == offTrack)
    return 1;
  else 
    return 0;
}

bool moreThanOne() {
  int rLeft = digitalRead(leftSensor);
  int rMid = digitalRead(midSensor);
  int rRight = digitalRead(rightSensor);
  int rMidLeft = digitalRead(midLeftSensor);
  int rMidRight = digitalRead(midRightSensor);

  if ((rLeft + rMid + rRight + rMidLeft + rMidRight) / 5 > 0.2)
    return 1;
  else
    return 0;
}

void loop() {

  if (digitalRead(midSensor) == onTrack) {
    while (digitalRead(midSensor) == onTrack)
      goForward();

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

// TODO:
// Expand the history capability to track all the sensors.
void writeHistory(int left, int mid, int right) {
  history[0] = left;
  history[1] = mid;
  history[2] = right;
}

