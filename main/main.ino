int leftMotor   = 5;
int rightMotor  = 3;

int leftSensor      = 10;
int midSensor       = 9;
int rightSensor     = 8;
int midLeftSensor   = 12;
int midRightSensor  = 11;

int highSpeed = 255;
int normalSpeed  = 0;
int lowSpeed  = 0;

int onTrack = 1;
int offTrack = 0;

int history[5] = {0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
}

bool blank() {
  int rLeft = digitalRead(leftSensor);
  int rMid = digitalRead(midSensor);
  int rRight = digitalRead(rightSensor);
  int rMidLeft = digitalRead(midLeftSensor);
  int rMidRight = digitalRead(midRightSensor);

  if (rLeft   == offTrack &&
    rMid      == offTrack &&
    rRight    == offTrack &&
    rMidLeft  == offTrack &&
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
  
  int rLeft = digitalRead(leftSensor);
  int rMid = digitalRead(midSensor);
  int rRight = digitalRead(rightSensor);
  int rMidLeft = digitalRead(midLeftSensor);
  int rMidRight = digitalRead(midRightSensor);

  if (rLeft + rMid + rRight + rMidRight + rMidLeft >= 3) {
    goForward();
    delay(100);
    if (blank()) {
      Serial.println("End.");
      while (1);
    }

  } else if (rMid == onTrack) {
    Serial.println("Going Forward.");
    goForward();

  } else if (rMidLeft == onTrack || rLeft == onTrack) {
      goRight();
      Serial.println("Going Right");

  } else if (rMidRight == onTrack || rRight == onTrack) {
      goLeft();
      Serial.println("Going Left");

  } else {
    Serial.println("Going Slow");
    goSlow();
  }

  writeHistory(rLeft, rMidLeft, rMid, rMidRight, rRight);

  delay(10);
}

void goForward() {
  analogWrite(leftMotor, highSpeed);
  analogWrite(rightMotor, highSpeed);
}

void goSlow() {
  analogWrite(leftMotor, highSpeed / 2);
  analogWrite(rightMotor, highSpeed / 2);
}

int anyone() {
  int rLeft = digitalRead(leftSensor);
  int rMid = digitalRead(midSensor);
  int rRight = digitalRead(rightSensor);
  int rMidLeft = digitalRead(midLeftSensor);
  int rMidRight = digitalRead(midRightSensor);

  if (rLeft || rMid || rRight || rMidLeft || rMidRight) {
    return 1;
  } else {
    return 0;
  }
}

void Stop() {
  Serial.println("Stopping");
  if (history[2] == onTrack)
  {
    while (anyone() == 0) {
      Serial.println("Cut in the track");
      goForward();
    }
  }
  delay(80);
  analogWrite(leftMotor, 0);
  analogWrite(rightMotor, 0);
}

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