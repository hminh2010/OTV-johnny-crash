// labeling the motors for their respective pins
int motor1a = 11;
int motor1b = 10;
int motor2a = 9;
int motor2b = 6;

#include <Stepper.h>
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
  
  myStepper.step(60);
  delay(500);
  setForward(255);
  delay(2000);
  stopMotors();
  
  myStepper.step(-60);
  delay(1000);
  setBackward(255);
  delay(2000);
  stopMotors();
  delay(10000000);
}
void setForward(int strength) {
  analogWrite(motor1a, strength);
  analogWrite(motor1b, 0); 
  analogWrite(motor2a, strength);
  analogWrite(motor2b, 0);
}

void setBackward(int strength) {
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