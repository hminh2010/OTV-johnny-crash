// labeling the motors for their respective pins
int motor1a = 11;
int motor1b = 10;
int motor2a = 9;
int motor2b = 6;

#include <Stepper.h>
#include "Enes100.h"
const int stepsPerRevolution =  200;
Stepper myStepper(stepsPerRevolution, 3, 4, 5, 8);

void setup() {
  pinMode(motor1a, OUTPUT);
  pinMode(motor1b, OUTPUT);
  pinMode(motor2a, OUTPUT);
  pinMode(motor2b, OUTPUT);

  myStepper.setSpeed(10);

  Serial.begin(9600);


}

void loop() {
  
  turn90();
  delay(10000);
  
}


void turn90Left() {
  for (int i = 0; i < 5; i++) {
    myStepper.step(60);
    setForward(200);
    delay(1000);
    stopMotors();
    
    myStepper.step(-64);
    setBackward(200);
    delay(1000);
    stopMotors();
  }
}

void turn90Left() {
  for (int i = 0; i < 5; i++) {
    myStepper.step(60);
    setForward(200);
    delay(1000);
    stopMotors();
    
    myStepper.step(-64);
    setBackward(200);
    delay(1000);
    stopMotors();
  }
}
void turn90_small() {
  for (int i = 0; i < 11; i++) {
    myStepper.step(60);
    setForward(200);
    delay(500);
    stopMotors();
    
    myStepper.step(-64);
    setBackward(200);
    delay(500);
    stopMotors();
  }
}

void setBackward(int strength) {
  analogWrite(motor1a, strength);
  analogWrite(motor1b, 0); 
  analogWrite(motor2a, strength);
  analogWrite(motor2b, 0);
}

//void turnUntil(int theta) {
//  myStepper.step(45);
//  Enes100.updateLocation();
//  while (abs(Enes100.location.theta - theta) > 1)
//  {
//    setForward(255);
//    delay(100);
//    Enes100.updateLocation();
//  }
//  stopMotors();
//  myStepper.step(-90);
//}

void setForward(int strength) {
  analogWrite(motor1a, 0);
  analogWrite(motor1b, strength); 
  analogWrite(motor2a, 0);
  analogWrite(motor2b, strength);
}

void stopMotors() {
  analogWrite(motor1a, 0);
  analogWrite(motor1b, 0); 
  analogWrite(motor2a, 0);
  analogWrite(motor2b, 0);
}
void skidSteer(int strength) {
  analogWrite(motor1a, strength);
  analogWrite(motor1b, 0); 
  analogWrite(motor2a, 0);
  analogWrite(motor2b, 0);
}
