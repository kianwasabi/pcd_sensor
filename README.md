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
- [SRF05 Ultrasonic Sensor](https://exp-tech.de/products/srf05-low-cost-ultrasonic-ranger) [or](https://www.robot-electronics.co.uk/htm/srf05tech.htm)
- Arduino Uno
- [CAN-BUS_Shield_V2.0](https://wiki.seeedstudio.com/CAN-BUS_Shield_V2.0/)
### Wiring

## CAN Frame
```bash 
Set data from ID: 0x200
0	A3	0	8	0	A4	
-----------------------------
Set data from ID: 0x200
0	6	0	3	0	4	
-----------------------------
```