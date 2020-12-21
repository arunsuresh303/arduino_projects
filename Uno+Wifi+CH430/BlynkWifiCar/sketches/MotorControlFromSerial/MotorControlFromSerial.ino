// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>
#include <Servo.h>

// DC motor on M2
AF_DCMotor motorLF(1);
AF_DCMotor motorLR(2);
AF_DCMotor motorRF(3);
AF_DCMotor motorRR(4);

// DC hobby servo
Servo servo1;

String input = "";

const int FULL_SPEED = 128;
const int HALF_SPEED = 64;

void setup() {
  Serial.begin(115200);           // set up Serial library at 9600 bps
  Serial.println("Motor party!");

}

void readSerial() {

  while (Serial.available() > 0)
  {
    char recieved = Serial.read();
    input += recieved;

    // Process message when new line character is recieved
    if (recieved == '\n')
    {

      int ind1 = input.indexOf(',');
      int ind2 = input.indexOf(',', ind1 + 1 );

      int xd = input.substring(0, ind1).toInt();
      int yd = input.substring(ind1 + 1).toInt();

       moveRover(xd, yd);

      input = ""; // Clear recieved buffer
    }
  }
}

void loop() {

  readSerial();

}

void moveRover(int x_direction, int y_direction) {
  if (x_direction == -1)
    if (y_direction == -1) {
      Serial.print("JOYSTICK: left-down DIRECTION: BACKWARD SOFT LEFT");
      Serial.print("  x_direction  ");
      Serial.print(x_direction);
      Serial.print("  y_direction  ");
      Serial.println(y_direction);

      motorLF.setSpeed(HALF_SPEED);//50% Speed of opposing side motors
      motorLR.setSpeed(HALF_SPEED);//50% Speed of opposing side motors
      motorRF.setSpeed(FULL_SPEED);
      motorRR.setSpeed(FULL_SPEED);

      motorLF.run(BACKWARD);
      motorLR.run(BACKWARD);
      motorRF.run(BACKWARD);
      motorRR.run(BACKWARD);

      //x = -1 and y = 0 Left on x axis
    } else if (y_direction == 0) {
      Serial.print("JOYSTICK: left DIRECTION: HARD LEFT ");
      Serial.print("  x_direction  ");
      Serial.print(x_direction);
      Serial.print("  y_direction  ");
      Serial.println(y_direction);

      motorLF.setSpeed(FULL_SPEED);
      motorLR.setSpeed(FULL_SPEED);
      motorRF.setSpeed(FULL_SPEED);
      motorRR.setSpeed(FULL_SPEED);

      motorLF.run(RELEASE);
      motorLR.run(RELEASE);
      motorRF.run(FORWARD);
      motorRR.run(FORWARD);

      //x = -1 and y = 1 Forward Diagonal Left
    } else {
      //y_direction == 1
      Serial.print("JOYSTICK left-up DIRECTION: FORWARD SOFT LEFT");
      Serial.print("  x_direction  ");
      Serial.print(x_direction);
      Serial.print("  y_direction  ");
      Serial.println(y_direction);

      motorLF.setSpeed(HALF_SPEED);//50% Speed of opposing side motors
      motorLR.setSpeed(HALF_SPEED);//50% Speed of opposing side motors
      motorRF.setSpeed(FULL_SPEED);
      motorRR.setSpeed(FULL_SPEED);

      motorLF.run(FORWARD);
      motorLR.run(FORWARD);
      motorRF.run(FORWARD);
      motorRR.run(FORWARD);

      //x = 0 and y = -1 Backward
    } else if (x_direction == 0)
    if (y_direction == -1) {
      Serial.print("JOYSTICK down DIRECTION BACKWARD");
      Serial.print("  x_direction  ");
      Serial.print(x_direction);
      Serial.print("  y_direction  ");
      Serial.println(y_direction);

      motorLF.setSpeed(FULL_SPEED);
      motorLR.setSpeed(FULL_SPEED);
      motorRF.setSpeed(FULL_SPEED);
      motorRR.setSpeed(FULL_SPEED);

      motorLF.run(BACKWARD);
      motorLR.run(BACKWARD);
      motorRF.run(BACKWARD);
      motorRR.run(BACKWARD);

      //x = 0 and y = 0 Stop
    } else if (y_direction == 0) {
      Serial.print("JOYSTICK: centered DIRECTION: STOP");
      Serial.print("  x_direction  ");
      Serial.print(x_direction);
      Serial.print("  y_direction  ");
      Serial.println(y_direction);

      motorLF.run(RELEASE);
      motorLR.run(RELEASE);
      motorRF.run(RELEASE);
      motorRR.run(RELEASE);

      //x = 0 and y = 1 Forward
    } else {
      //y_direction == 1
      Serial.print("JOYSTICK: up DIRECTION: FORWARD");
      Serial.print("  x_direction  ");
      Serial.print(x_direction);
      Serial.print("  y_direction  ");
      Serial.println(y_direction);

      motorLF.setSpeed(FULL_SPEED);
      motorLR.setSpeed(FULL_SPEED);
      motorRF.setSpeed(FULL_SPEED);
      motorRR.setSpeed(FULL_SPEED);

      motorLF.run(FORWARD);
      motorLR.run(FORWARD);
      motorRF.run(FORWARD);
      motorRR.run(FORWARD);

      //x = 1 and y = -1 Backward Diagonal Right
    } else
    //x_direction == 1
    if (y_direction == -1) {
      Serial.print("JOYSTICK right-down DIRECTION: BACKWARD SOFT RIGHT");
      Serial.print("  x_direction  ");
      Serial.print(x_direction);
      Serial.print("  y_direction  ");
      Serial.println(y_direction);

      motorLF.setSpeed(FULL_SPEED);
      motorLR.setSpeed(FULL_SPEED);
      motorRF.setSpeed(HALF_SPEED);//50% Speed of opposing side motors
      motorRR.setSpeed(HALF_SPEED);//50% Speed of opposing side motors

      motorLF.run(BACKWARD);
      motorLR.run(BACKWARD);
      motorRF.run(BACKWARD);
      motorRR.run(BACKWARD);

      //x = 1 and y = 0 Right on x-axis
    } else if (y_direction == 0) {
      Serial.print("JOYSITCK: right DIRECTION: HARD RIGHT");
      Serial.print("  x_direction  ");
      Serial.print(x_direction);
      Serial.print("  y_direction  ");
      Serial.println(y_direction);

      motorLF.setSpeed(FULL_SPEED);
      motorLR.setSpeed(FULL_SPEED);
      motorRF.setSpeed(FULL_SPEED);
      motorRR.setSpeed(FULL_SPEED);

      motorLF.run(FORWARD);
      motorLR.run(FORWARD);
      motorRF.run(RELEASE);
      motorRR.run(RELEASE);

      //x = 1 and y = 1 Forward Diagonal Right
    } else {
      //y_direction == 1
      Serial.print("JOYSTICK: right-up DIRECTION: SOFT RIGHT");
      Serial.print("  x_direction  ");
      Serial.print(x_direction);
      Serial.print("  y_direction  ");
      Serial.println(y_direction);

      motorLF.setSpeed(FULL_SPEED);
      motorLR.setSpeed(FULL_SPEED);
      motorRF.setSpeed(HALF_SPEED);//50% Speed of opposing side motors
      motorRR.setSpeed(HALF_SPEED);//50% Speed of opposing side motors

      motorLF.run(FORWARD);
      motorLR.run(FORWARD);
      motorRF.run(FORWARD);
      motorRR.run(FORWARD);
    }


}

void stopRover() {
  Serial.println("ROVER STOP!");

  motorLF.run(RELEASE);
  motorLR.run(RELEASE);
  motorRF.run(RELEASE);
  motorRR.run(RELEASE);
}
