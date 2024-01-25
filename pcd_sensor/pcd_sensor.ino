#include <NewPing.h>
//#include <can-serial.h>
#include <mcp2515_can.h>
//#include <mcp_can.h>
// serial monitor 
#define BAUD_RATE 115200
// sonar 
#define SONAR_NUM     3 // Number of sensors.
#define MAX_DISTANCE 400 // Maximum distance (in cm) to ping.
#define PING_INTERVAL 33 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).
// can
#define CAN_SAMPLE_RATE CAN_500KBPS   // CAN bus speed
// pins 
#define CAN_HAT_CS_PIN 9
#define SENSOR_0_TRIG_PIN 7           
#define SENSOR_0_ECHO_PIN 7
#define SENSOR_1_TRIG_PIN 6
#define SENSOR_1_ECHO_PIN 6
#define SENSOR_2_TRIG_PIN 5
#define SENSOR_2_ECHO_PIN 5
// sonar
unsigned long pingTimer[SONAR_NUM]; // Holds the times when the next ping should happen for each sensor.
unsigned int cm[SONAR_NUM];         // Where the ping distances are stored.
uint8_t currentSensor = 0;          // Keeps track of which sensor is active.
NewPing sonar[SONAR_NUM] = {     // Sensor object array with each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(SENSOR_0_TRIG_PIN, SENSOR_0_ECHO_PIN, MAX_DISTANCE), 
  NewPing(SENSOR_1_TRIG_PIN, SENSOR_1_ECHO_PIN, MAX_DISTANCE), 
  NewPing(SENSOR_2_TRIG_PIN, SENSOR_2_ECHO_PIN, MAX_DISTANCE), 
};
// can 
const unsigned long can_id = 0x200;    // CAN Device address
const int can_dlc = 3;                 // CAN message data length (number of bytes in frame)
uint8_t data[can_dlc];                 // CAN message payload
mcp2515_can CAN(CAN_HAT_CS_PIN);       // CAN Bus object

void setup() {
  CAN.begin(CAN_SAMPLE_RATE);
  Serial.begin(BAUD_RATE);
  pingTimer[0] = millis() + 75;           // First ping starts at 75ms, gives time for the Arduino to chill before starting.
  for (uint8_t i = 1; i < SONAR_NUM; i++) {// Set the starting time for each sensor.
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
  }
}

void loop() {
  // Loop through all the sensors.
  for (uint8_t i = 0; i < SONAR_NUM; i++) { 
    // Is it this sensor's time to ping?
    if (millis() >= pingTimer[i]) {         
      // Set next time this sensor will be pinged.
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;  
      // Sensor ping cycle complete, do something with the results.
      if (i == 0 && currentSensor == SONAR_NUM - 1){  
        oneSensorCycle();
      } 
      // Make sure previous timer is canceled before starting a new ping (insurance).
      sonar[currentSensor].timer_stop();  
      // Sensor being accessed.        
      currentSensor = i;              
      // Make distance zero in case there's no ping echo for this sensor.            
      cm[currentSensor] = 0;                      
      // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
      sonar[currentSensor].ping_timer(echoCheck); 
    }
  }
  // Other code that *DOESN'T* analyze ping results.
}

/* If ping received, set the sensor distance to array. */
void echoCheck() { 
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;   
}

/* Sensor ping cycle complete, do something with the results. */
void oneSensorCycle() { 
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    // Printing lines
        Serial.print("Sensor");
        Serial.print(i);
        Serial.print(":");
        Serial.println(cm[i]);
    // Sending bytes to CAN 
        // byte reading_high = highByte(cm[i]);
        // byte reading_low = lowByte(cm[i]);
        // byte packet[]={0x59,0x59,i,reading_high,reading_low};
        // Serial.write(packet, sizeof(packet));
  }
}