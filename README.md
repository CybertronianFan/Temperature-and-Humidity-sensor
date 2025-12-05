# Temperature and Humidity Sensor for Arduino

This is my project of coding a DHT11 Temperature and Humidity module to detect temperature and humidity and output it onto a 16x2 LCD screen



By CybertronianFan on GitHub.



Parts List:



1 x Arduino Uno (This is the one I used but I believe others can be used)

1 x DHT11 Temperature and Humidity module (I used a 3-pin version for this project, but I believe the 4 pin version can be used too with very similar steps to the ones below)

1 x LCD1602 Module

1 x 10K Ohm Potentiometer

1 x 830 Tie-Points Breadboard

16 x Male to Male jumper wires

3 x Male to Female jumper wires



Connection Guide:



1. Connect the 5V Arduino pin to the + rail on the breadboard. (Make sure the Arduino Uno isn't being given power during this connection period).

2\. Connect the ground Arduino pin to the - rail on the breadboard.

3\. Connect the LCD pins onto to the breadboard (Make sure it is on the regular rails and not the power rails on the side).

4\. Place the potentiometer across the "bridge" of the breadboard.

5\. Using Male to Female jumper cables connect the DHT11 VCC and ground pins to the breadboard power rails and the signal pin to digital pin 2 on the Arduino Uno.

6\. Connect the potentiometer to the power and ground rails of the breadboard and connect the output to the VO pin of the LCD.

7\. Connect the LCD VSS, RW and K pins to the ground rail.

8\. Connect the VDD and A pins to the power rail.

9\. Connect the RS pin of the LCD to digital pin 7, E pin to digital pin 8, D4 pin to digital pin 9, D5 pin to digital pin 10, D6 pin to digital pin 11 and D7 pin to digital pin 12.



Coding instructions:



Copy paste the code titled "TaHs\_Code" into Arduino IDE and upload it to the Arduino Uno. 

