#include <Stepper.h>
#include "Enes100.h"

#define echoPinY 2
#define trigPinY 7
#define echoPinX 12
#define trigPinX 13

int motor1B = 11;
int motor1F = 10;
int motor2B = 9;
int motor2F = 6;

long duration;
int distance;

boolean startAtTop;

// possible heights: 26.5cm, 19.1cm, 14cm

const int STEPS_PER_REV =  200;
Stepper myStepper(STEPS_PER_REV, 3, 4, 5, 8);

void setup() {
    Serial.begin(9600);
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

    while (!Enes100.begin("Johnny Crash", CRASH_SITE, 11, 2, 7)) {
        Serial.println("Failed to connect, trying again...");
    }
    Enes100.println("Crash Site successfully began.");

    startAtTop = Enes100.destination.y < 1; 
    
    Enes100.print("Starting at Top? ");
    Enes100.println(startAtTop);
    
    myStepper.setSpeed(50);

    Enes100.println("Now attempting turn");
    
    if (startAtTop) {
      turnUntil(-M_PI/2);
    } else {
      turnUntil(M_PI/2);
    } 

    Enes100.print("After turn Theta: ");
    Enes100.println(Enes100.location.theta);
    Enes100.print(getWidth());
  setForward(255);
  
    
  boolean arrivedAtMission = false;  
  while (!arrivedAtMission) {
      if (getDistanceX() < 10) {
        stopMotors();
      arrivedAtMission = true;
      Enes100.println("arrived at mission");
    }
  }
  
  delay(10000);
  Enes100.println("Turning to wall 1");
  if (startAtTop) { 
    turnUntil(M_PI/2);
  }
  Enes100.println("Turning east");
  turnUntil(0);

  setForward(255);
  delay(3000);
  stopMotors(); 
  
  Enes100.println("Turning to wall 2");
  turnUntil(M_PI/2);
  
  setForward(255);

  Enes100.println("Going to wall");
  
  boolean reachedWall = false;
  while (!reachedWall) {
    if (getDistanceX() < 5) {
      stopMotors();
      reachedWall = true;
    }
  }

  turnUntil(0);
  setForward(255);
//
//  boolean arrivedAtMission = false;
//  boolean arrivedAtEnd = false;
//  

//  
//  delay(10000); 
//  
//  setBackward(255);
//  delay(2000);
//  
//  
//  if (startAtTop) {
//    turn180();
//  }
//  turn90Right(); 
//
//  delay(5000);
//
//  setForward(255);
//

  
}

void loop() {
  

}

void turnUntil(int theta) {
  Enes100.updateLocation();
  while (abs(Enes100.location.theta - theta) > 0.6)
  {
    turn1Iter();
    Enes100.println("1 iter");
    Enes100.print("Theta: ");
    Enes100.println(Enes100.location.theta);
    Enes100.updateLocation();
    delay(500);
  }
}

int getDistanceX() {
    digitalWrite(trigPinX, LOW);
    delay(20);
    digitalWrite(trigPinX, HIGH);
    delay(100);
    digitalWrite(trigPinX, LOW);
    duration = pulseIn(echoPinX, HIGH);
    distance = duration * 0.034 / 2;
    return distance;
}

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

int getWidth() {
    updateLocation();
    int d1 = getDistanceX();
    int d2 = abs(Enes100.destination.x - Enes100.location.x);
    return 2*(d2-d1);
}

void turn180() {
  myStepper.step(-30);
  setForward(200);
  delay(2000);
  stopMotors();
  for (int i = 0; i < 6; i++) {
    myStepper.step(80);
    setBackward(200);
    delay(2000);
    stopMotors();

    myStepper.step(-80);
    setForward(200);
    delay(2000);
    stopMotors();
  }
  
  delay(100);
  myStepper.step(40);
}

void turn90Right() {
  myStepper.step(-30);
  setForward(200);
  delay(1000);
  stopMotors();
  
  for (int i = 0; i < 9; i++) {
    myStepper.step(80);
    setBackward(200);
    delay(1000);
    stopMotors();

    myStepper.step(-80);
    setForward(200);
    delay(1000);
    stopMotors();
  }
}

void turn1Iter() { //est. 15 degrees
  myStepper.step(-30);
  setForward(200);
  delay(700);
  stopMotors();
  
  myStepper.step(80);
  setBackward(200);
  delay(1000);
  stopMotors();

  myStepper.step(-50);
  setForward(200);
  delay(700);
  stopMotors();

  
}

void setForward(int strength) {
  analogWrite(motor1B, 0);
  analogWrite(motor1F, strength); 
  analogWrite(motor2B, 0);
  analogWrite(motor2F, strength);
}

void stopMotors() {
  analogWrite(motor1B, 0);
  analogWrite(motor1F, 0); 
  analogWrite(motor2B, 0);
  analogWrite(motor2F, 0);
}

void setBackward(int strength) {
  analogWrite(motor1B, strength);
  analogWrite(motor1F, 0); 
  analogWrite(motor2B, strength);
  analogWrite(motor2F, 0);
}