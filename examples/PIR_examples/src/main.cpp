/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>

// Variables
uint8_t DEBUG=1;
unsigned long sleep_delay=1000; //milliseconds
unsigned long led_on_time=1000; //milliseconds
unsigned long led_off_time=200; //milliseconds

// Pin Assignment
const int PIR_pin= 2;



const byte led_pin = LED_BUILTIN;
const byte interruptPin = 2;
volatile byte state = LOW;

void motion_detected() {
  //state = !state;
  if (DEBUG) { Serial.println("Motion detected"); }
  //digitalWrite(ledPin, state);
  digitalWrite(led_pin, HIGH); // LED on 1
  delay(led_on_time);
  digitalWrite(led_pin, LOW); // LED off

}


void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), motion_detected, RISING);

  //DEBUG
  if (DEBUG)
  {
    Serial.begin(9600);
    Serial.println("Debug: Startup");
  }
}

void loop() {
    delay(sleep_delay);
}
