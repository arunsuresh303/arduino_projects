// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!


#include <Servo.h>
#define echoPin A2 // attach pin A2 Arduino to pin Echo of HC-SR04
#define trigPin A3 //attach pin A3 Arduino to pin Trig of HC-SR04


// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement


// DC hobby servo
Servo servo1;


void setup() {

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(115200); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}


// Test the  servo
void loop() {

  if (calculateDistance() < 10) {
    
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    triggerServo();
  } else {
    servo1.detach();
  }

}

int calculateDistance() {

  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor

  return distance;

}

void triggerServo() {
  Serial.print("Attaching Servo to pin 9...\n");
  servo1.attach(9);
  Serial.print("Writing current position...\n");
  servo1.write (20);

}
