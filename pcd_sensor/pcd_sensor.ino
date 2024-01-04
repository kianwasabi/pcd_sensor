#include <can-serial.h>
#include <mcp2515_can.h>
#include <mcp_can.h>

#define CAN_HAT_CS_PIN 9               // CAN HAT Pin
#define TRIG_PIN  13                   // Ultrasonic sensor trigger pin
#define ECHO_PIN  12                   // Ultrasonic sensor echo pin
#define BAUD_RATE 9600
#define CAN_SAMPLE_RATE CAN_500KBPS   // CAN bus speed


const unsigned long can_id = 0x200;    // CAN Device address
const int can_dlc = 2;                 // CAN message data length (number of bytes in frame)
uint8_t data[can_dlc];                 // CAN message payload

mcp2515_can CAN(CAN_HAT_CS_PIN);

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  CAN.begin(CAN_SAMPLE_RATE);
  Serial.begin(BAUD_RATE);
}

int measure_distance() 
{ 
  // shut down the trigger pin to avoide interference 
  digitalWrite(TRIG_PIN, LOW); 
  delay(5);

  // trigger the sensor
  digitalWrite(TRIG_PIN, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TRIG_PIN, LOW);  

  // PulseIn -> measure time until signal comes back
  long duration = pulseIn(ECHO, HIGH);  
  Serial.println(duration);
  // Calculate the distance (in cm) based on the speed of sound.  
  unsigned long distance = (duration / 2) * 0.03432; 
  Serial.println(duration);
  return distance;
}

void send_to_can(long distance) {
  // shift 8 bits to the right and mask with 0xFF to get the first byte
  data[0] = (distance >> 8) & 0xFF; 
  // mask with 0xFF to get the second byte     
  data[1] = distance & 0xFF;          
  // send to CAN Bus   
  CAN.sendMsgBuf(can_id, CAN_STDID ,can_dlc, data);
}

void loop()  {
  long distance = measure_distance();
  send_to_can(distance);
  delay(100);
 }