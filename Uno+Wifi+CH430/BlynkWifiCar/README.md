# Wifi Controlled Rover 

![alt text](https://github.com/arunsuresh303/arduino_projects/blob/main/Uno+Wifi+CH430/BlynkWifiCar/images/roverfinished.jpg?raw=true)


## Overview
In this project, i have built a rover which can be controlled using a mobile app over Wifi. Arduino Genuino Uno board does not have built-in WiFi. There are methods to connect ESP8266 to Arduino to enable Wifi, but those methods are not for beginners like me. Alternatively, you could use NodeMCU or Lolin D1 boards for your WiFi projects, which are really good options if your are starting new. In my case, i had already purchased L293D Motor Shield for UNO. I didnt want to invest further, on motor shields and wanted to reuse the parts which i had already purchased for my UNO board.

Enter [RobotDyn UNO+WiFi+CH430](https://robotdyn.com/uno-wifi-r3-atmega328p-esp8266-32mb-flash-usb-ttl-ch340g-micro-usb.html). This is basically two boards combined into one - Arduino UNO and ESP8266. And there is also the CH430 chip, which to put simply is a USB to Serial converter. But this board doesn't work like the Official Arduino UNO WiFi board, which seamlessly integrates WiFi with UNO. You get a bunch of DIP switches on the board, which lets you toggle between ATmega328(UNO) and ESP8266 while uploading sketches. There is also one combination, where you can make ATmega328 and ESP8266 communicate to each other using the single Serial port of the board. All the DIP switch combinations are listed out in the product webpage. For convenience, i have pasted the same below:

| Mode | 1  | 2  | 3  | 4 | 5  | 6  | 7  | 8  |
|:----------|:----------|:----------|:----------|:----------|:----------|:----------|:----------|:----------|
| CH340 connect to ESP8266 (upload sketch) | OFF   | OFF    | OFF    | OFF  | ON    | ON   | ON    | No Use   |
| CH340 connect to ESP8266 (connect)    | OFF   | OFF   | OFF  | OFF    | ON    | ON   | OFF    | No Use   |
| CH340 connect to ATmega328 (upload sketch)   | OFF    | OFF   | ON    | ON    | OFF    | OFF    | OFF    | No Use   |
| Mega328+ESP8266  | ON    | ON    | OFF    | OFF   | OFF   | OFF    | OFF  | No Use   |
| All modules work independent   | OFF    | OFF    | OFF   | OFF    | OFF    | OFF    | OFF    | No Use   |



Its a shame, that there is only one serial. Once you hook up ATmega328 and ESP8266, there is no way to debug via the Serial Monitor of the IDE. You would have to debug each modules separately. There is a "Mega" version of this board, which has more serials to spare which will solve this problem, but it also costs more.



### Parts Needed

- RobotDyn UNO+WiFi+CH430 Board
- 4WD Chassis Kit 
 	- Acrylic Boards
 	- 4 DC Motors
	- 4 Rubber Tyres
 	- Battery Pack/ Battery Holder
 	- Switch
- L293D Motor Shield for UNO
- Jumper Wires
- PC/Macbook
- USB-microUSB cable (for uploading sketches)
- Mobile Phone (Android/iPhone)
- Tons of patience

## Get Cracking
### Blynk to connect to WiFi
First of all, we need a remote. What better device than a reliable mobile phone to fulfil this purpose.
[Blynk](https://blynk.io/) is an IoT platform, which lets you connect your devices to the cloud. They also offer a mobile app, which lets you control your device using widgets. The app is available on both Apple App Store and Google Play.

Install the Blynk library on your Arduino IDE. See the screenshot below for reference. This example uses version 0.6.1 vrsion of the library.

![alt text](https://github.com/arunsuresh303/arduino_projects/blob/main/Uno+Wifi+CH430/BlynkWifiCar/images/blynklibrary.png?raw=true)

Install the Blynk app on your device and create an account. Create a new peoject. Choose ESP8266 as the device. Blynk will send an Auth Token to your email after you create your project. We need this token in our ESP8266 sketch. Create your remote using the widgets provided in the app. Since we are going to control a rover, a joystick widget would best suit our requirements. Use Virtual Pin "V1". See screenshot below for reference. Map the joystick values from 0 - 255. When the joystick is at center position, both X and Y would have 127 as their values.

![alt text](https://github.com/arunsuresh303/arduino_projects/blob/main/Uno+Wifi+CH430/BlynkWifiCar/images/blynknewproject.PNG?raw=true)
![alt text](https://github.com/arunsuresh303/arduino_projects/blob/main/Uno+Wifi+CH430/BlynkWifiCar/images/blynknewproject2.PNG?raw=true)
![alt text](https://github.com/arunsuresh303/arduino_projects/blob/main/Uno+Wifi+CH430/BlynkWifiCar/images/blynknewproject3.PNG?raw=true)
![alt text](https://github.com/arunsuresh303/arduino_projects/blob/main/Uno+Wifi+CH430/BlynkWifiCar/images/widgetbox.PNG?raw=true)
![alt text](https://github.com/arunsuresh303/arduino_projects/blob/main/Uno+Wifi+CH430/BlynkWifiCar/images/widgetjoystick.PNG?raw=true)

The widgets would transmit the X and Y axis values to your sketch running on the ESP8266 module (Next section describes this in detail).


### Sketch to receive joystick input from the app on ESP8266

UNO+WiFi+CH430 is basically 2 separate boards put together into one. The ESP8266 part of the board handles the WiFi connection. Anything to do with WiFi, you need to set it up on this board. For most of the cases, you only need to work with ESP8266 as it is more than capable to deal with most of the requirements. However we need to use the L293D motor shield for Arduino, hence we need to split the tasks between the boards.

ESP8266 will connect to your home WiFi and your capp can communicate with it. This sketch will translate inputs received from the app's virtual joystick to a more simple direction values. We will get into the details soon. Once the translation is done, we will simply print it to the serial port. Arduino will listen to this serial port and gather the direction inputs from ESP8266 and instruct the motors to run appropriately.

After installing the Arduino IDE, make sure you do the following steps:


1. Open the IDE preferences/settings window and enter the following in the the "Additional Boards Manager URLs" : http://arduino.esp8266.com/stable/package_esp8266com_index.json

![alt text](https://github.com/arunsuresh303/arduino_projects/blob/main/Uno+Wifi+CH430/BlynkWifiCar/images/boardmanager.png?raw=true)


2. Open "Boards Manager" on the IDE and search for ESP8266. Install the latest version. I am using version 2.7.4 in my sketches.

![alt text](https://github.com/arunsuresh303/arduino_projects/blob/main/Uno+Wifi+CH430/BlynkWifiCar/images/addesp8266board.png?raw=true)

3. Change the board to "Generic ESP8266 Module". See screenshot for reference.

![alt text](https://github.com/arunsuresh303/arduino_projects/blob/main/Uno+Wifi+CH430/BlynkWifiCar/images/esp8266board.png?raw=true)

4. Copy the sketch from [here](https://github.com/arunsuresh303/arduino_projects/blob/main/Uno%2BWifi%2BCH430/BlynkWifiCar/sketches/JoystickControl/JoystickControl.ino) and change the SSID to your WiFi name, update your WiFi password and finally also update the Blynk token which was sent to you when you created an account there. Make sure your WiFi is on 2.4Ghz.

![alt text](https://github.com/arunsuresh303/arduino_projects/blob/main/Uno+Wifi+CH430/BlynkWifiCar/images/wifiparameters.png?raw=true)

5. Change the DIP switches of your UNO+WiFi board as shown below and connect the USB cable to your PC/Macbook. Compile and upload the sketch.

| 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  |
|:----------|:----------|:----------|:----------|:----------|:----------|:----------|:----------|
| OFF    | OFF   | OFF   | OFF   | ON    | ON   | ON    | NO USE    |

6. Disconnect the USB cable. Change the DIP switches as shown below and reconnect the USB cable to your PC/Macbook.

| 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  |
|:----------|:----------|:----------|:----------|:----------|:----------|:----------|:----------|
| OFF    | OFF   | OFF   | OFF   | ON    | ON   | OFF    | NO USE    |


7. Open "Serial Monitor" on the IDE. Change baud rate to 115200 (our sketches use 115200 baud rate). If your blynk library was able to connect to your WiFi, you will see something like this on the serial monitor.

![alt text](https://github.com/arunsuresh303/arduino_projects/blob/main/Uno+Wifi+CH430/BlynkWifiCar/images/blynkconnection.png?raw=true)

8. Open Blynk app on your mobile phone, hit the play button on the top right corner. The app should connect to your board. Try moving the joystick around. You should see some numbers getting printed on the serial monitor. These numbers are directions which will be sentto Arduino. You sketch translated the joystick X and Y axes values to directions. For example "0,0" means STOP, "1,1" means FORWARD, 0,1 means HARD RIGHT etc.

![alt text](https://github.com/arunsuresh303/arduino_projects/blob/main/Uno+Wifi+CH430/BlynkWifiCar/images/joysticktest.png?raw=true)

### Sketch to receive rover directions from ESP8266 on UNO

Once you are done with the ESP8266 sketch. We need to upload a sketch to Arduino UNO. This second sketch will convert the direction values received from ESP8266 to motion.

Follow the steps below:
1. Change the board to "Arduino UNO". See screenshot for reference.

![alt text](https://github.com/arunsuresh303/arduino_projects/blob/main/Uno+Wifi+CH430/BlynkWifiCar/images/arduinounoboard.png?raw=true)


2. Change the DIP switches of your UNO+WiFi board as shown below and connect the USB cable to your PC/Macbook. Compile and upload the [sketch](https://github.com/arunsuresh303/arduino_projects/blob/main/Uno%2BWifi%2BCH430/BlynkWifiCar/sketches/MotorControlFromSerial/MotorControlFromSerial.ino).You can change the motor's speed values as per your preference in the sketch. I have used a full speed value of 128 and half speed value of 64. 

| 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  |
|:----------|:----------|:----------|:----------|:----------|:----------|:----------|:----------|
| OFF    | OFF   | ON   | ON   | OFF    | OFF   | OFF    | NO USE    |

3. Disconnect the USB cable and reconnect it. Open Serial Monitor. Change baud rate to 115200 (our sketches use 115200 baud rate). Now we need to test whether the sketch is working correctly. We can simulate ESP8266 sending direction values by directly entering values like 0,0 or 1,1 in the serial monitor's input. You should see response from the board on the Serial Monitor as shown below.

![alt text](https://github.com/arunsuresh303/arduino_projects/blob/main/Uno+Wifi+CH430/BlynkWifiCar/images/serialtest.png?raw=true)

4. Disconnect the USB cable. Change the DIP switches of your UNO+WiFi board as shown below. In this setting, UNO and ESP8266 will talk to each other over the serial port.

| 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  |
|:----------|:----------|:----------|:----------|:----------|:----------|:----------|:----------|
| ON    | ON   | OFF   | OFF   | OFF    | OFF   | OFF    | NO USE    |


### Connecting to L293D Motor Shield and Chassis

Setup your Rover Chassis. You can follow this [video](https://www.youtube.com/watch?v=uW8YVcBjPGU) for instructions. Please note all chassis are not same, so you need to follow the instructions for your chassis. Follow the steps below to connect your motors to the shield.

1. Align the pins of L293D Motor Shield with that of your board and snap it in to place.

2. Connect the wires of your motors on the left side to M1 and M2 on the shield.

3. Connect the wires of your motors on the right side to M3 and M4 on the shield.

4. You may choose to power both the shield and your board using a single battery pack or provide separate power supplys to them. I prefer the latter, as this gives more power for the motors.

5. IMPORTANT: if you are using separate pwer supplys, make sure you remove the power jumper on the Motor Shield.

[PUT SCREENSHOTS HERE]

### Test the rover

Remove the wheels from the chassis.

Turn on the power supply. LED indicators on both Motor Shield and UNO+Wifi should light up. 

Open Blynk app on your mobile device. If all is well, you should see your board connected to the app.

![alt text](https://github.com/arunsuresh303/arduino_projects/blob/main/Uno+Wifi+CH430/BlynkWifiCar/images/wifistatus.PNG?raw=true)

Try moving the joystick, the motors should turn. If they do, enjoy the satisfaction for a moment. If they dont, head to the trouble shooting section.

Put the wheels back on and take your rover for a spin.

## Troubleshooting

1. LEDs on the boards dont light up:
	- Check power supply. Make sure it has enough juice. Use at least a 9V battery pack.

2. You heard a humming sound from motors, but they do not rotate.
	- Check power supply. Make sure it has enough juice. Use at least a 9V battery pack.
	- Consider providing separate power supplys to Shield and Board.
3. LEDs light up, but no response to joystick.
	- Make sure DIP switched are : ON ON OFF OFF OFF OFF OFF OFF 
	- Make sure that the baud rates on both sketches are the same. You specify the baud rate in the Serial.begin statement in the setup() method.

 