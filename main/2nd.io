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
void goForward(int speed = highSpeed);

void setup() {
  Serial.begin(9600);
}

bool blank() {
  int rLeft = digitalRead(leftSensor);
  int rMid = digitalRead(midSensor);
  int rRight = digitalRead(rightSensor);
  int rMidLeft = digitalRead(midLeftSensor);
  int rMidRight = digitalRead(midRightSensor);

  if (rLeft + rRight + rMidRight + rMidLeft + rMid == 0)
    return 1;
  else 
    return 0;
}

bool anyone() {
  int rLeft = digitalRead(leftSensor);
  int rMid = digitalRead(midSensor);
  int rRight = digitalRead(rightSensor);
  int rMidLeft = digitalRead(midLeftSensor);
  int rMidRight = digitalRead(midRightSensor);

  if (rLeft || rMid || rRight || rMidLeft || rMidRight)
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

int lastone = 0;

void loop() {
  int mid = 0;
  int midleft = 0;
  int midright = 0;
  int right = 0;
  int left = 0;

  if (digitalRead(midSensor) == onTrack) {
    while (digitalRead(midSensor) == onTrack) {
      goForward();
    }
    mid = 1;

  } else if (digitalRead(midLeftSensor) == onTrack) {
    while (digitalRead(midSensor) == offTrack && blank() == 0 && moreThanOne() == 0)
      goRight();
    midleft = 1;

  } else if (digitalRead(leftSensor) == onTrack) {
    while (digitalRead(midLeftSensor) == offTrack && blank() == 0 && moreThanOne() == 0)
      goFullRight();
    left = 1;

  } else if (digitalRead(midRightSensor) == onTrack) {
    while (digitalRead(midSensor) == offTrack && blank() == 0 && moreThanOne() == 0)
      goLeft();
    midright = 1;

  } else if (digitalRead(rightSensor) == onTrack) {
    while (digitalRead(midRightSensor) == offTrack && blank() == 0 && moreThanOne() == 0)
      goFullLeft();
    right = 1;
  }

  writeHistory(left, midleft, mid, midright, right);
  Stop();
}

void goForward(int speed = highSpeed) {
  analogWrite(leftMotor, speed);
  analogWrite(rightMotor, speed);
}

void Stop() {
  if (history[0] + history[1] + history[2] + history[3] + history[4] >= 1)
  {
    while (anyone() == 0)
      goForward();
  } else {
    delay(30);
    analogWrite(leftMotor, 0);
    analogWrite(rightMotor, 0);
  }
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

