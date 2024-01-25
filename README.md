# pcd_sensor
Ultrasound Sensor Array with the SRF05
Estimate distance and position of solid objects using multiple low-cost ultrasound sensors.

## Introduction
Using the cheap SRF05 ultrasonic sensor and an Arduino we can build a low cost sensor array for robotics. 
The Arduino code will poll all the sensors and send byte packets via CAN BUS with the index and the distance.

For measuring the distances we use a sonar technique to calculate the time of flight of the sound. 
The SRF05 is very inaccurate for distance measurement but can be used as a cheap low level fail-safe system for proximity object detection in order to avoid hitting obstacles during navigation.

The main benefits of using an array of sensors versus using one sensor and one servo to sweep is accuracy and no delay to measure positional distance of a huge area in front of the array. 
Currently using an array of 3 sensors we can poll all of them several times per second without any interference. 
Also having extra mechanical complexity like a servo will make the hardware more prone to failure.

## Code
This example code was used to successfully communicate with 15 ultrasonic sensors. 
You can adjust the number of sensors in your project by changing SONAR_NUM and the number of NewPing objects in the
"sonar" array. 
You also need to change the pins for each sensor for the NewPing objects. Each sensor
is pinged at 33ms intervals. So, one cycle of all sensors takes 495ms (33 * 15 = 495ms). 

The results are sent to the "oneSensorCycle" function which currently just displays the distance data. 
Your project would normally process the sensor results in this function (for example, decide if a robot needs to
turn and call the turn function). Keep in mind this example is event-driven. Your complete sketch needs
to be written so there's no "delay" commands and the loop() cycles at faster than a 33ms rate. If other
processes take longer than 33ms, you'll need to increase PING_INTERVAL so it doesn't get behind.

## Reference: 
https://www.hackster.io/user04650005/ultrasound-sensor-array-with-the-hc-sr04-f7108f

## CAN: 
CAN-BUS Shield V2.0
Pin 7,6,5 are free to use for the sensors. 

https://wiki.seeedstudio.com/CAN-BUS_Shield_V2.0/