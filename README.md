# Ultrasound Sensor Array for Park Distance Control
Ultrasound Sensor Array with the SRF05 Sensors, Arduino Nano and Seeed CAN-BUS Shield V2.0. <br>
Estimate distance of solid objects using multiple low-cost ultrasound sensors. <br>

## Introduction
Using the cheap SRF05 ultrasonic sensor and an Arduino Uno with a CAN Hat we can build a low cost sensor array for robotics or automotiv applications. <br>
The Arduino code will poll all the sensors and send each sensors' measured distance in cm in byte frame format to the CAN BUS. <br>

For measuring the distances we use a sonar technique to calculate the time of flight of the sound. <br>
The SRF05 is very inaccurate for distance measurement but can be used as a cheap low level fail-safe system for proximity object detection.

The main benefits of using an array of sensors versus using one sensor and one servo to sweep is accuracy and no delay to measure positional distance of a huge area in front of the array. <br>
Currently using an array of 3 sensors we can poll all of them several times per second without any interference. <br>
Th code was successfully tested to communicate with 15 ultrasonic sensors. 

Source: [Ultrasound Sensor Array with the HC-SR04](https://www.hackster.io/user04650005/ultrasound-sensor-array-with-the-hc-sr04-f7108f)

## System
### Hardware 
- [SRF05 Ultrasonic Sensor](https://www.robot-electronics.co.uk/htm/srf05tech.htm)
- [Arduino Uno R3](https://eckstein-shop.de/HIMALAYAbasicUNOR3ATmega328PBoardATmega16U2mitUSBKabelArduinoUnoR3kompatibelEN)
- [CAN-BUS_Shield_V2.0](https://wiki.seeedstudio.com/CAN-BUS_Shield_V2.0/)

### Wiring
The SRF05 sensors operate in Mode 2 (Single pin for both Trigger and Echo). <br>
The brigded sensor pins can be connected to a as "FREE labled pin of the CAN HAT. <br>
![T](https://files.seeedstudio.com/wiki/CAN_BUS_Shield/image/PINMAP.png)

## CAN Frame
The maximum distance that can be measured is 400cm. <br> 
Therfore we need 2 bytes in the CAN frames' payload for each sensor. <br>
The can frame is structured as follows: <br>

Byte 0 - 1: Sensor 0 <br>
Byte 2 - 3: Sensor 1 <br>
Byte 4 - 5: Sensor 2 <br>

```bash 
Set data from ID: 0x200
0	A3	0	8	0	A4	
-----------------------------
Set data from ID: 0x200
0	6	0	3	0	4	
-----------------------------
```