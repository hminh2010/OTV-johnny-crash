#include "Enes100.h"
#include <Stepper.h>

#define echoPinY 2
#define trigPinY 7
#define echoPinX 12
#define trigPinX 13

int motor1B = 11;
int motor1F = 10;
int motor2B = 9;
int motor2F = 6;



// possible heights: 26.5cm, 19.1cm, 14cm
// max stepper is 60

const int STEPS_PER_REV =  200;

long duration;
int distance;
int height;
int width1;
int width2;
int abnormalSide; // Number 1-4 denoting which side is abnormal, number corresponding to which side depends on mission site location
boolean startAtTop; 
int missionTurn;

int motorStrength = 0; 

void setup() {
    Stepper myStepper(STEPS_PER_REV, 3, 4, 5, 8);
    // SENSOR SETUP

    // Ultrasonic Y
    pinMode(trigPinY, OUTPUT); 
    pinMode(echoPinY, INPUT); 
    // Ultrasonic X
    pinMode(trigPinX, OUTPUT); 
    pinMode(echoPinX, INPUT);
    
    // MOTOR SETUP
    pinMode(motor1B, OUTPUT);
    pinMode(motor1F, OUTPUT);
    pinMode(motor2B, OUTPUT);
    pinMode(motor2F, OUTPUT);
    
    // CONNECTING TO VISION SYSTEM
    while (!Enes100.begin("Johnny Crash", CRASH_SITE, 420, 7, 8)) {
        Enes100.println("Failed to connect, trying again...");
    }
    Enes100.println("Crash Site successfully began.");

    // DETECTING INITAL ROBOT POSITION
    updateLocation();
    // MISSION SITE COORDINATES: Enes100.destination.x; Enes100.destination.y;

    // TURN ROBOT TOWARDS MISSION SITE
    if (Enes100.location.y > 1) {
      startAtTop = True;
      turnUntil(-1.5707);
    } else {
      startAtTop = False;
      turnUntil(1.5707);
    }
    while (getDistanceX() > 2) {
      setForward(255);
    
    }
    

    // MOVE ROBOT TO MISSION SITE AND DETERMINE X DIMENSION OF THE ABORNAMLITY
    


    // LOOP EACH SIDE TO DETERMINE REFLECTANCE VALUES
    // assumes the robot starts normal to the mission site and facing the x = 0 wall
    
    // read the height and read the infrared sensor values

    if (startAtTop) { // if it starts at the top it needs to turn right
        missionTurn = -90;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
    }
    
    height = getDistanceY();
    for (int count = 1; count < 5; count++) {

        if (isAbnormal()) {
            abnormalSide = count;

            Enes100.print("Abnormal Side Found: ")
            Enes100.println(count)
            break;

        } 
    }
    
    // add code to account for if the robot is even lined up properly 
    
    // turn to next side and repeat

    // 


    // FINISH AND MAYBE PLACE ARUCO MARKER

    // START NAVIGATING THE OBSTACLES
    Enes100.updateLocation();
    if (Enes100.location.y > 1) {
        goUntilY(.9);
        turnUntil(0);
        goUntilX(.1);
        turnUntil(M_PI/2);
        goUntilY(1.9);
        turnUntil(M_PI);
        goUntilX(4.0);
    } else {
        goUntilY(1.9);
        turnUntil(M_PI/2);
        goUntilX(4.0);
    }

    // SENSE WHEN STUCK

while (Enes100.location.x < 4) {
    Enes100.updateLocation;
    double x = Enes100.location.x;
    Delay (4500);
    Enes100.updateLocation;
    if (Enes100.location.X > (x-0.1) && Enes100.location.X < (x+0.1) {
        stopMotors();
        setBackward(255);
        Delay(1000);
        stopMotors();
        turnUntil(M_PI);
        setForward(255);
    }
} 

    // GO UNDERNEATH THE LIMBO

    
}

void loop() {

}

/*
    Updates Location using Enes100 module, with extra print statements for debugging
*/
void updateLocation() {
    if (Enes100.updateLocation()) {
        Enes100.print("Updated Location: ");
        Enes100.print(Enes100.location.x);
        Enes100.print(",");
        Enes100.print(Enes100.location.y);
        Enes100.print(" Theta: ");
        Enes100.print(Enes100.location.theta);
    } else {
        Enes100.print("Update Location failed.");
    }
}

/*
    Turn until reach the angle param (using ENES vision system)
*/

void turnUntil(int theta) {
  myStepper.step(60);
  Enes100.updateLocation();
  while (abs(Enes100.location.theta - theta) > 1)
  {
    setForward(255);
    Enes100.updateLocation();
  }
  stopMotors();
  myStepper.step(-60);
}

/*
    Turn until reach the x param
*/
void goUntilX(int x) {
    while(Enes100.location.X < (x-0.1) || Enes100.location.X > (x+0.1)) {
        Enes100.updateLocation();
        setForward(255);
    }
    stopMotors();
}

/*
    Turn until reach the y param
*/
void goUntilY(int y) {
    while(Enes100.location.Y < (y-0.1) || Enes100.location.Y > (y+0.1)) {
        Enes100.updateLocation;
        setForward(255);
    }
    stopMotors();
}



/*
    Get distance measured from Ultrasonic sensor on the pole (reads downwards in -y direction)
    This distance is given in centimeters
*/
int getDistanceY() {
    // Clears the trigPin condition
    digitalWrite(trigPinY, LOW);
    delay(20);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPinY, HIGH);
    delay(100);
    digitalWrite(trigPinY, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2;
    return distance;
}
/*
    Get distance measured from Ultrasonic sensor on the bot (reads in x direction)
    This distance is given in centimeters
*/
int getDistanceX() {
    // Clears the trigPin condition
    digitalWrite(trigPinX, LOW);
    delay(20);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPinX, HIGH);
    delay(100);
    digitalWrite(trigPinX, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2;
    return distance;
}

boolean readSide() {
    int readingLowtom = determineAbnormalityLow();
    int readingHigh = determineAbnormalityHigh();
}

/*
    Reads reflectance value from the bottom reflectance sensor
    Analog pin: A0
*/
int determineAbnormalityHigh() {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);
    // print out the value you read:
    if (sensorValue > 700){
    Serial.println("abnormal");
    Serial.println(sensorValue);
    } else {
    Serial.println("normal");
    Serial.println(sensorValue);
    }
    return sensorValue;
}

/* 
    Reads reflectance value from the bottom reflectance sensor 
    Analog pin: A1 
*/
int determineAbnormalityLow() {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A1);
    // print out the value you read:
    if (sensorValue > 700){
    Serial.println("abnormal");
    Serial.println(sensorValue);
    } else {
    Serial.println("normal");
    Serial.println(sensorValue);
    }
    return sensorValue;
}

int calculateHeight() {
  digitalWrite(12, HIGH);
  digitalWrite(trigPin, LOW);
  delay(200);
  digitalWrite(trigPin, HIGH);
  delay(100);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return 32 - distance;
}

boolean detectStuck() {
    updateLocation();
    if (motorStrength != 0 ) { // then the vehicle should be moving 
        
    }
}

boolean isAbnormal() { // note: black is > 800
    int sensorValue = 0;
    totalTakes = 5;
    for (int count = 0; count < totalTakes; count++) {
        highReading = determineAbnormalityHigh();
        lowReading = determineAbnormalityLow()
        sensorValue += (lowReading > highReading) ? lowReading : highReading; // adds larger value to the average
    }
    if (sensorValue / totalTakes < 800){
        return false;
        } else {
        return true;
    }

}

void setForward(int strength) {
  analogWrite(motor1B, strength);
  analogWrite(motor1F, 0); 
  analogWrite(motor2B, strength);
  analogWrite(motor2F, 0);
  motorStrength = strength;
}

void setBackward(int strength) {
  analogWrite(motor1B, 0);
  analogWrite(motor1F, strength); 
  analogWrite(motor2B, 0);
  analogWrite(motor2F, strength);
  motorStrength = -strength;
}

void stopMotors() {
  analogWrite(motor1B, 0);
  analogWrite(motor1F, 0); 
  analogWrite(motor2B, 0);
  analogWrite(motor2F, 0);
    motorStrength = 0;
}