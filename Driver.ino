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

Stepper myStepper(stepsPerRevolution, 3, 4, 5, 8);

// possible heights: 26.5cm, 19.1cm, 14cm
// max stepper is 60

const int STEPS_PER_REV =  200;

long duration;
int distance;
int height;
int width1;
int width2;

int motorStrength = 0; 

void setup() {

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

    // MOVE ROBOT TO MISSION SITE AND DETERMINE X DIMENSION OF THE ABORNAMLITY

    // LOOP EACH SIDE TO DETERMINE REFLECTANCE VALUES

    // FINISH AND MAYBE PLACE ARUCO MARKER

    // START NAVIGATING THE OBSTACLES

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
    while (abs(Enes100.location.theta - theta) > 1) {
        
    }
}

/*
    Turn until reach the x param
*/
void goUntilX(int x) {

}

/*
    Turn until reach the y param
*/
void goUntilY(int y) {

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
  height = 32 - distance;
  return height;
}

boolean detectStuck() {
    updateLocation();
    if (motorStrength != 0 ) { // then the vehicle should be moving 
        
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