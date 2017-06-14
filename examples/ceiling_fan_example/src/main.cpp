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
const uint8_t fan_relay0_pin = A0;
const uint8_t fan_relay1_pin = A1;
const uint8_t fan_relay2_pin = A3;
const uint8_t light_relay_pin = 9;



////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////
uint8_t count;
uint8_t fan;
uint8_t light;




////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//// Functions
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void activate_ceiling_fan(uint8_t fan, uint8_t light){
  // exclusive relay activation for fan
  // non-exclusive relay activation for light

  if(light){
    digitalWrite(light_relay_pin, HIGH);
    if(DEBUG){Serial.println("Ceiling light: on");}
  }else{
    digitalWrite(light_relay_pin, LOW);
    if(DEBUG){Serial.println("Ceiling light: off");}
  }

  if(fan != 0x00 && fan != 0x01 && fan != 0x02 && fan != 0x04){
    // make sure multiple fan coils are nor powered
    if(DEBUG){
      Serial.print("ERROR: fan var=");
      Serial.print(fan);
      Serial.println(": fan relay is not exclusive or is nonsesical, keeping previous settings\n");}
    return;
  }
  if(fan & 0x01){
    digitalWrite(fan_relay0_pin, HIGH);
    if(DEBUG){Serial.println("Fan Relay 0: on");}
  }else{
    digitalWrite(fan_relay0_pin, LOW);
    if(DEBUG){Serial.println("Fan Relay 0: off");}
  }
  if(fan & 0x02){
    digitalWrite(fan_relay1_pin, HIGH);
    if(DEBUG){Serial.println("Fan Relay 1: on");}
  }else{
    digitalWrite(fan_relay1_pin, LOW);
    if(DEBUG){Serial.println("Fan Relay 1: off");}
  }
  if(fan & 0x04){
    digitalWrite(fan_relay2_pin, HIGH);
    if(DEBUG){Serial.println("Fan Relay 2: on");}
  }else{
    digitalWrite(fan_relay2_pin, LOW);
    if(DEBUG){Serial.println("Fan Relay 2: off");}
  }
  if(DEBUG){Serial.println("");}
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


  pinMode(fan_relay0_pin, OUTPUT);
  pinMode(fan_relay1_pin, OUTPUT);
  pinMode(fan_relay2_pin, OUTPUT);
  pinMode(light_relay_pin, OUTPUT);
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

  for(int i=0;i<16;i++){

    fan = i;
    light = 1;
    activate_ceiling_fan(fan, light);
    delay(1000);//delays 100ms

    light = 0;
    activate_ceiling_fan(fan, light);
    delay(1000);//delays 100ms

  }



}
