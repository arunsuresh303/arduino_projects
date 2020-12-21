// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!


#include <Servo.h>


// DC hobby servo
Servo servo1;

String input = "";
boolean isTrigger = false;

void setup() {

  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Servo party!");

}


// Test the  servo by inputing any string via serial monitor
void loop() {

  readSerial();

}

void readSerial() {

  if (Serial.available()) {
    
    input = Serial.readString();
    input.trim();
    
    Serial.print("Input: ");
    Serial.print(input);
    Serial.println();

    if (input.equals("1")) {
      triggerServo();
    } else if (input.equals("0")) {
      stopServo();
    }

  }

}

void triggerServo() {

  if (!servo1.attached()) {
    Serial.print("Starting Servo\n");
    servo1.attach(9);
    servo1.write (50);
  } 

  

}

void stopServo() {

  if (servo1.attached()) {
    Serial.print("Stopping Servo \n");
    servo1.detach();
  }

}
