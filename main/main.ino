int leftMotor   = 5;
int rightMotor  = 3;

int leftSensor      = 10;
int midSensor       = 9;
int rightSensor     = 8;
int midLeftSensor   = 12;
int midRightSensor  = 11;

int highSpeed = 255.;
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
  
  int rLeft = digitalRead(leftSensor);
  int rMid = digitalRead(midSensor);
  int rRight = digitalRead(rightSensor);
  int rMidLeft = digitalRead(midLeftSensor);
  int rMidRight = digitalRead(midRightSensor);

  if (digitalRead(midSensor)) {
    while (digitalRead(midSensor)) {
      Serial.println("Going Forward.");
      goForward();
    }
  }

  else if (digitalRead(midLeftSensor) == onTrack) {
    while (digitalRead(midSensor) == offTrack && moreThanOne() == 0) {
      goRight();
      Serial.println("Going Right");
      Serial.println("midSensor offTrack");
    }

  } else if (digitalRead(leftSensor) == onTrack) {
    while (digitalRead(midSensor) == offTrack && moreThanOne() == 0) {
      goRight();
      Serial.println("Going Right");
      Serial.println("midSensor offTrack");
    }

  } else if (digitalRead(midRightSensor) == onTrack) {
    while (digitalRead(midSensor) == offTrack && moreThanOne() == 0) {
      goLeft();
      Serial.println("Going Left");
      Serial.println("midSensor offTrack");
    }

  } else if (digitalRead(rightSensor) == onTrack) {
    while (digitalRead(midSensor) == offTrack && moreThanOne() == 0) {
      goLeft();
      Serial.println("Going Left");
      Serial.println("midSensor offTrack");
    }
  } else {
    Stop();
  }

  writeHistory(rLeft, rMidLeft, rMid, rMidRight, rRight);

  delay(10);
}

void goForward() {
  analogWrite(leftMotor, highSpeed);
  analogWrite(rightMotor, highSpeed);
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
  delay(30);
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