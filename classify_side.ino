#include "Enes100.h"
#define echoPin 2
#define trigPin 4

// possible heights: 26.5cm, 19.1cm, 14cm


long duration;
int distance;
int height;
int width1;
int width2;

void setup() {
  // put your setup code here, to run once:
  Enes100.begin("crash site team", CRASH_SITE, 9, 7, 8);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(12, OUTPUT);
  Serial.println(calculateHeight());

}

void loop() {
  Enes100.updateLocation(); 
  int sensorValue = analogRead(A5);
  if (sensorValue > 700) {
    Serial.print("Abnormal: ");
  } else {
    Serial.print("Not Abnormal: ");
  }
  Serial.println(sensorValue);
  delay(1000);

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
  height = 17 - distance;
  return height;
}