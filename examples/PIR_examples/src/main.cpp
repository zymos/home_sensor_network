

#include <Arduino.h>

// Variables
uint8_t DEBUG=1;
unsigned long sleep_delay=1000; //milliseconds
unsigned long led_on_time=1000; //milliseconds
unsigned long led_off_time=200; //milliseconds

// Pin Assignment

const uint8_t led_pin = LED_BUILTIN;
const uint8_t PIR_pin = 3;

// Variables
uint8_t motion_detected;
uint8_t motion_count;

///////////////////////////////////////////////////////////////
// Primatives
///////////////////////////////////////////////////////////////
void motion_started(void);
void motion_stoped(void);
void detect_motion(void);
void init_PIR(void);


///////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////

void motion_started(void){
  // function preformed when motion is first detected
  if (DEBUG) { Serial.println("Motion actions started"); }
}
void motion_stoped(void){
  // function preformed when motion is finally stoped
  if (DEBUG) { Serial.println("Motion actions stoped"); }
}

void detect_motion(void) {
  // Total delay is motion_delay*delay_count after motion stops
  uint16_t motion_delay=500; //ms
  uint8_t delay_count=30;
  if(motion_detected){ // function already active, reset count and exit
    motion_count = 0; //reset count
    return;
  }
  motion_detected = 1;
  motion_started();
  while(motion_count <= delay_count){ // ensures a delay before turning off
    while(digitalRead(PIR_pin)){ // Motion is still being detected
      if (DEBUG) { Serial.println("Motion detected"); }
      motion_count = 0; // reset count
      delay(motion_delay);
    }
    if (DEBUG) { Serial.println("Motion stoped, waiting..."); }
    motion_count++; // increment count
    delay(motion_delay);
  }
  if (DEBUG) { Serial.println("No more motion detected"); }
  motion_count = 0;
  motion_detected = 0;
  motion_stoped();
}



void init_PIR(void){
  pinMode(PIR_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIR_pin), detect_motion, RISING);
}


void setup() {
  pinMode(led_pin, OUTPUT);

  //DEBUG
  if (DEBUG)
  {
    Serial.begin(9600);
    Serial.println("Debug: Startup");
  }
  init_PIR();
}

void loop() {
    delay(sleep_delay);
}
