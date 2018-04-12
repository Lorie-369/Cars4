
int motorLeft   = 4;
int motorRight  = 3;

int sensorLeft  = 10;
int sensorMid   = 9;
int sensorRight = 8;

int lastRead[3] = {0, 0, 0};

// White 0
// Black 1

void setup() {
  Serial.begin(9600);
}

void loop() {
  int rLeft   = digitalRead(sensorLeft);
  int rRight  = digitalRead(sensorRight);
  int rMid    = digitalRead(sensorMid);

  for (int i = 0; i < 3; i++) {
      Serial.print(lastRead[i]); Serial.print(" ");
    }
   Serial.print("\n");
   
  if (rLeft == 1 && rRight == 1 && rMid == 1) {
    Serial.print("All Black ");
    if (lastRead[0] == 0 && lastRead[1] == 1 && lastRead[2] == 0) {
      Stop();
      Serial.print("Stop");
    }
    else {
      goForward();
      Serial.print("Forward");
    }
    Serial.print("\n");
  }
  else if (rLeft == 0 && rRight == 0 && rMid == 1) {
    goForward();
  }
  else if (rLeft == 0 && rRight == 1 && rMid == 0) {
    goLeft();
  }
  else if (rLeft == 1 && rRight == 0 && rMid == 0) {
    goRight();
  }
  else {
    delay(1000);
    Stop();
    Serial.println("else Stop");
  }
  writeHistory(rLeft, rMid, rRight);
  delay(10);
}

void goForward() {
  digitalWrite(motorLeft, HIGH);
  digitalWrite(motorRight, HIGH);
}

void Stop() {
  digitalWrite(motorLeft, LOW);
  digitalWrite(motorRight, LOW);
}

void goLeft() {
  digitalWrite(motorLeft, HIGH);
  digitalWrite(motorRight, LOW);
}

void goRight() {
  digitalWrite(motorLeft, LOW);
  digitalWrite(motorRight, HIGH);
}

void writeHistory(int left, int mid, int right) {
  lastRead[0] = left;
  lastRead[1] = mid;
  lastRead[2] = right;
}

