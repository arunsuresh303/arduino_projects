# Simple Serial Communication Between ESP8266 and UNO


This is a simple project which demonstrates the serial communication between ESP8266 and UNO boards.
The sketch in ESP8266 board is a simple one, which writes 1 and 0 to the serial port every 2 seconds.
The sketch in the UNO board, reads the serial and runs a a continuous servo motor when it receives 1 and stops the motor when it receives 0. The servo is connected to pin 9 of the UNO board.

You can also try the same, by simply tunring on and off an LED.

Ensure that the baud rates in both sketches are same.

Ensure the DIP switch positions are correctly maintained while uploading the respective sketches.


| Mode | 1  | 2  | 3  | 4 | 5  | 6  | 7  | 8  |
|:----------|:----------|:----------|:----------|:----------|:----------|:----------|:----------|:----------|
| CH340 connect to ESP8266 (upload sketch) | OFF   | OFF    | OFF    | OFF  | ON    | ON   | ON    | No Use   |
| CH340 connect to ESP8266 (connect)    | OFF   | OFF   | OFF  | OFF    | ON    | ON   | OFF    | No Use   |
| CH340 connect to ATmega328 (upload sketch)   | OFF    | OFF   | ON    | ON    | OFF    | OFF    | OFF    | No Use   |
| Mega328+ESP8266  | ON    | ON    | OFF    | OFF   | OFF   | OFF    | OFF  | No Use   |
| All modules work independent   | OFF    | OFF    | OFF   | OFF    | OFF    | OFF    | OFF    | No Use   |



