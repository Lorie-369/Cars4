/*
    Author:  Amr Essam
    Project: Cars 4 – Arduino Line Follower Robot.
*/

// *-- Motors --*
// Working for forward only, backward pins can be added.
#define leftMotor 5
#define rightMotor 3

// *-- Sensors --*
// You can read the output as digital or analog for advanced purposes.
// Digital pins:
#define leftSensor 10
#define midSensor 9
#define rightSensor 8
#define midLeftSensor 12
#define midRightSensor 11

// A Photoresistor is used to continue the run after stopping.
// Edit the pin number to fit your connections.
#define photoRes A0

// The normal running speed, adjust it according to the
// battery power, the track, the car size, and its weight.
//
// 200 may be too fast.
// Analog Range: 0 - 255 --> 0 volt - Motors given voltage.
// 
// As long as you don't need the ability of variable speeds during the run,
// leave them defined, and if you need this ability, change them to variables.
#define highSpeed 200

// A slow speed for cuts in the track
#define slowSpeed highSpeed * .60 // 60% the highSpeed. (Adjust it)

// An optional low speed, for turning right and left.
#define lowSpeed 0

// Sensor's digital output, 1 for blacks, 0 for whites.
#define onTrack 1
#define offTrack 0

void setup() {
    // Don't forget to use the serial monitor while debugging your code.
    // Mostly all of the movements are printed to the serial, in
    // case you wanted to track the robot's movements.
    Serial.begin(9600);
}

/*
   The function checks instantly if the robot is on a blank spot.
   Which means all the sensors are reading white (0).
  
   The function returns 1 if true, and 0 if false.
*/
bool blank() {
    int rLeft = digitalRead(leftSensor);
    int rMid = digitalRead(midSensor);
    int rRight = digitalRead(rightSensor);
    int rMidLeft = digitalRead(midLeftSensor);
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
    // Use analogRead() function to get more accurate values, not just 0 & 1.
    int rLeft     = digitalRead(leftSensor);
    int rMid      = digitalRead(midSensor);
    int rRight    = digitalRead(rightSensor);
    int rMidLeft  = digitalRead(midLeftSensor);
    int rMidRight = digitalRead(midRightSensor);
    
    /*
       *-- SPECIAL CASE AND CAN BE REMOVED. --*
       If more than 2 sensors are detecting the black line, suppose it's on
       an intersection, and move forward till a blank spot is detected and stop.
    */
    if (rLeft + rMid + rRight + rMidRight + rMidLeft >= 3) {
        Serial.println("Start of the delay...");
        goForward();
        delay(200);
        Serial.println("End of the delay.");

        if (blank()) {
            analogWrite(leftMotor, 0);
            analogWrite(rightMotor, 0);
            Serial.println("End.");

            // Just touch the photoresistor to decrease its resistance
            // and break out of the while loop and continue the run.
            //
            // Adjust this number according to the resistance used.
            while (analogRead(photoRes) > 70);

            Serial.println("Continue.");
        }
    }

    // The basic bang-bang method.
    // The midLeft and midRight sensors are used to increase the accuracy of the run.
    else if (rMid == onTrack) {
        goForward();
        Serial.println("Going Forward.");

    } else if (rMidLeft == onTrack || rLeft == onTrack) {
        goRight();
        Serial.println("Going Right");

    } else if (rMidRight == onTrack || rRight == onTrack) {
        goLeft();
        Serial.println("Going Left");

    } else {
        goSlow();
        Serial.println("Going Slow");
    }

    // Refresh Rate. (CAN BE EDITED OR REMOVED)
    delay(10);
}

// Run with highSpeed
void goForward() {
    analogWrite(leftMotor, highSpeed);
    analogWrite(rightMotor, highSpeed);
}

// Run with slowSpeed
void goSlow() {
    analogWrite(leftMotor, slowSpeed);
    analogWrite(rightMotor, slowSpeed);
}

// Turn with highSpeed & lowSpeed
void goLeft() {
    analogWrite(leftMotor, highSpeed);
    analogWrite(rightMotor, lowSpeed);
}

void goRight() {
    analogWrite(leftMotor, lowSpeed);
    analogWrite(rightMotor, highSpeed);
}
