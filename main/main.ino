int leftMotor   = 5;
int rightMotor  = 3;

int leftSensor      = 10;
int midSensor       = 9;
int rightSensor     = 8;
int midLeftSensor   = 12;
int midRightSensor  = 11;

int highSpeed = 120;
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

  if ((rLeft + rMid + rRight) >= 2) {
    Serial.println("Intersection, Going Forward for 200ms delay.");
    goForward();
    delay(200);
    Serial.println("Intersection, delay end.");

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

  } else if (rLeft == onTrack) {
    goRight();
    Serial.println("Going Right");

  } else if (rRight == onTrack) {
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
