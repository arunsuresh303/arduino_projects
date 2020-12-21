// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
#include <Servo.h>

// DC motor on M2
AF_DCMotor leftFront(1);
AF_DCMotor leftRear(2);
AF_DCMotor rightFront(3);
AF_DCMotor rightRear(4);

// DC hobby servo
Servo servo1;


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor party!");

  // turn on servo
  servo1.attach(9);

  // turn on motor #1
  leftFront.setSpeed(200);
  leftFront.run(RELEASE);

  // turn on motor #2
  leftRear.setSpeed(200);
  leftRear.run(RELEASE);

  // turn on motor #3
  rightFront.setSpeed(200);
  rightFront.run(RELEASE);

  // turn on motor #4
  rightRear.setSpeed(200);
  rightRear.run(RELEASE);
}


void loop() {
  goBackAndForth();
  doClockWiseTurn();
  doCounterClockWiseTurn();
}

void goBackAndForth() {

  delay(10000);
  leftFront.run(FORWARD);
  leftRear.run(FORWARD);
  rightFront.run(FORWARD);
  rightRear.run(FORWARD);
  delay(3000);

  leftFront.run(RELEASE);
  leftRear.run(RELEASE);
  rightFront.run(RELEASE);
  rightRear.run(RELEASE);
  delay(1000);

  leftFront.run(BACKWARD);
  leftRear.run(BACKWARD);
  rightFront.run(BACKWARD);
  rightRear.run(BACKWARD);
  delay(3000);

  leftFront.run(RELEASE);
  leftRear.run(RELEASE);
  rightFront.run(RELEASE);
  rightRear.run(RELEASE);
  

}

void doClockWiseTurn() {

  delay(3000);
  leftFront.run(FORWARD);
  leftRear.run(FORWARD);
  rightFront.run(BACKWARD);
  rightRear.run(BACKWARD);
  delay(5000);

  leftFront.run(RELEASE);
  leftRear.run(RELEASE);
  rightFront.run(RELEASE);
  rightRear.run(RELEASE);
  

}


void doCounterClockWiseTurn() {

  delay(3000);
  leftFront.run(BACKWARD);
  leftRear.run(BACKWARD);
  rightFront.run(FORWARD);
  rightRear.run(FORWARD);
  delay(5000);

  leftFront.run(RELEASE);
  leftRear.run(RELEASE);
  rightFront.run(RELEASE);
  rightRear.run(RELEASE);
  

}

