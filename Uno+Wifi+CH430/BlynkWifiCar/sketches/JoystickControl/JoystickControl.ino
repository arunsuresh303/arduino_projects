/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "<YOUR BLYNK AUTH TOKEN>";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "<YOUR SSID>";
char pass[] = "<YOUR SSID PASSWORD>";


//Control motion of motors
BLYNK_WRITE(V1) {
  
  const int X_THRESHOLD_LOW = 108; //x: 128 - 20
  const int X_THRESHOLD_HIGH = 148; //x: 128 + 20   

  const int Y_THRESHOLD_LOW = 90; //y: 128 - 20
  const int Y_THRESHOLD_HIGH = 200; //y: 128 + 20
      
  int x_position = param[0].asInt();  //Read the Blynk Joystick x Position 0-255
  int y_position = param[1].asInt();  //Read the Blynk Joystick y Position 0-255

  int x_direction;  //Variable for Direction of Joystick Movement: x= -1, 0, 1
  int y_direction;  //Variable for Direction of Joystick Movement: y= -1, 0, 1

  String output = "";
 
//Determine the direction of the Joystick Movement

  x_direction = 0;
  y_direction = 0;

  if (x_position > X_THRESHOLD_HIGH) {
    x_direction = 1;
  } else if (x_position < X_THRESHOLD_LOW) {
    x_direction = -1;
  }
  if (y_position > Y_THRESHOLD_HIGH) {
    y_direction = 1;
  } else if (y_position < Y_THRESHOLD_LOW) {
    y_direction = -1;
  }

  //Send direction details to Arduino using serial interface
  output = output + x_direction + "," + y_direction;

    //Ensure the motors really stop
    if(output.equals("0,0")){
      for(int i=0;i<5;i++){
        Serial.println(output);
      }
    }else
    Serial.println(output);

  
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}
