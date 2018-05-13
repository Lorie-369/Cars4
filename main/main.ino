int leftMotor   = 5;
int rightMotor  = 3;

int leftSensor      = 17;
int midSensor       = 16;
int rightSensor     = 14;
int midLeftSensor   = 15;
int midRightSensor  = 14;

int highSpeed = 200;
int slowSpeed  = highSpeed * .60; // 60% the highSpeed.
int lowSpeed  = 0;

int onTrack = 1;
int offTrack = 0;

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

void loop() {
  
  int rLeft = digitalRead(leftSensor);
  int rMid = digitalRead(midSensor);
  int rRight = digitalRead(rightSensor);
  int rMidLeft = digitalRead(midLeftSensor);
  int rMidRight = digitalRead(midRightSensor);

  if (rLeft + rMid + rRight + rMidRight + rMidLeft >= 3) {
    goForward();
    delay(200);

    if (blank()) {
      analogWrite(leftMotor, 0);
      analogWrite(rightMotor, 0);
      Serial.println("End.");

      while (analogRead(A0) > 70);
      Serial.println("Continue.");
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

  // Refresh Rate.
  delay(10);
}

void goForward() {
  analogWrite(leftMotor, highSpeed);
  analogWrite(rightMotor, highSpeed);
}

void goSlow() {
  analogWrite(leftMotor, slowSpeed);
  analogWrite(rightMotor, slowSpeed);
}

void goLeft() {
  analogWrite(leftMotor, highSpeed);
  analogWrite(rightMotor, lowSpeed);
}

void goRight() {
  analogWrite(leftMotor, lowSpeed);
  analogWrite(rightMotor, highSpeed);
}
