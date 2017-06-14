/////////////////////////////////////////////////////////////////////////
//                            Sensor network
//
// Ref
//  http://www.learningaboutelectronics.com/Articles/Arduino-liquid-level-sensor-circuit.php
/////////////////////////////////////////////////////////////////////////


#include "Arduino.h"


//#include <Narcoleptic.h> //low-power sleep


//////////////////////////////////////////////////////////////////////////
// Configuration
//////////////////////////////////////////////////////////////////////////

const uint8_t DEBUG=1; // Debug sends serial-port output


// alarm


// Pin Assignment
const uint8_t relay0_pin = 9;
const uint8_t relay1_pin = A0;
const uint8_t relay2_pin = A1;
const uint8_t relay3_pin = A3;



////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////
uint8_t count;
uint8_t relays;




////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//// Functions
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void activate_relays(uint8_t relays){
  // non-exclusive relay activation
  if(relays & 0x01){
    digitalWrite(relay0_pin, HIGH);
    if(DEBUG){Serial.println("Relay 0: on");}
  }else{
    digitalWrite(relay0_pin, LOW);
    if(DEBUG){Serial.println("Relay 0: off");}
  }
  if(relays & 0x02){
    digitalWrite(relay1_pin, HIGH);
    if(DEBUG){Serial.println("Relay 1: on");}
  }else{
    digitalWrite(relay1_pin, LOW);
    if(DEBUG){Serial.println("Relay 1: off");}
  }
  if(relays & 0x04){
    digitalWrite(relay2_pin, HIGH);
    if(DEBUG){Serial.println("Relay 2: on");}
  }else{
    digitalWrite(relay2_pin, LOW);
    if(DEBUG){Serial.println("Relay 2: off");}
  }
  if(relays & 0x08){
    digitalWrite(relay3_pin, HIGH);
    if(DEBUG){Serial.println("Relay 3: on\n");}
  }else{
    digitalWrite(relay3_pin, LOW);
    if(DEBUG){Serial.println("Relay 3: off\n");}
  }
}



////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//// Initial setup
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void setup(void)
{
  //DEBUG
  if (DEBUG){
    Serial.begin(9600);
    Serial.println("Debug: Startup");
    count = 0;
  }


  pinMode(relay0_pin, OUTPUT);
  pinMode(relay1_pin, OUTPUT);
  pinMode(relay2_pin, OUTPUT);
  pinMode(relay3_pin, OUTPUT);
}


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//// LOOP forever
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
void loop(void){
  // DEBUG
  if (DEBUG){
    Serial.println(".......................");
    Serial.print("Running (loop)... ");
    Serial.println(count);
    count++;
  }

  relays = 0x01;
  activate_relays(relays);
  delay(1000);//delays 100ms

  relays = 0x02;
  activate_relays(relays);
  delay(1000);//delays 100ms

  relays = 0x04;
  activate_relays(relays);
  delay(1000);//delays 100ms

  relays = 0x08;
  activate_relays(relays);
  delay(1000);//delays 100ms

  relays = 0x01;
  activate_relays(relays);
  delay(1000);//delays 100ms

  relays = 0x03;
  activate_relays(relays);
  delay(1000);//delays 100ms

  relays = 0x07;
  activate_relays(relays);
  delay(1000);//delays 100ms

  relays = 0x0f;
  activate_relays(relays);
  delay(1000);//delays 100ms
}
