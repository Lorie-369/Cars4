int leftMotor  = 5;
int rightMotor = 3;

int leftSensor     = 10;
int midLeftSensor  = 12;
int midSensor      = 9;
int midRightSensor = 11;
int rightSensor    = 8;

// Adjust the speed according to the motor.
int highSpeed   = 140;
int normalSpeed = 0;
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

  if ((rLeft + rMid + rRight + rMidLeft + rMidRight) / 5 == 0)
    return 1;
  else
    return 0;
}

int intersection() {
  int rLeft     = digitalRead(leftSensor);
  int rMid      = digitalRead(midSensor);
  int rRight    = digitalRead(rightSensor);
  int rMidLeft  = digitalRead(midLeftSensor);
  int rMidRight = digitalRead(midRightSensor);

  if ((rLeft + rMid + rRight + rMidLeft + rMidRight) / 5 >= 0.8)
    return 1;
  else
    return 0;
}

void loop() {

}

void goForward() {
  analogWrite(leftMotor, highSpeed);
  analogWrite(rightMotor, highSpeed);
}

void Stop() {
  // if (history[2] == onTrack) {
  //   delay(1000);
  // }
  // else
  //   delay(25);

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