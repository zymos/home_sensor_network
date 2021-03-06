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
const uint8_t address0_pin = 8;
const uint8_t address1_pin = 7;
const uint8_t address2_pin = 6;
const uint8_t address3_pin = 5;



////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////
uint8_t count;
uint8_t address;




////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//// Functions
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

uint8_t aquire_address(void){
  address = 0xff;
  address |= digitalRead(address3_pin); // reads into first digit
  address <<= 1; // shifts
  address |= digitalRead(address2_pin); // reads into first digit
  address <<= 1;// shifts
  address |= digitalRead(address1_pin);// reads into first digit
  address <<= 1;  // shifts
  address |= digitalRead(address0_pin);// reads into first digit
  address = ~address; // Pull up resistors mean inverted
  if (DEBUG){
    Serial.print("Address(bin) is: ");
    Serial.print(not(digitalRead(address3_pin)));
    Serial.print(not(digitalRead(address2_pin)));
    Serial.print(not(digitalRead(address1_pin)));
    Serial.println(not(digitalRead(address0_pin)));
    Serial.print("Address is: ");
    Serial.println(address);
  }
  return address;
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

  pinMode(address0_pin, INPUT_PULLUP);
  pinMode(address1_pin, INPUT_PULLUP);
  pinMode(address2_pin, INPUT_PULLUP);
  pinMode(address3_pin, INPUT_PULLUP);
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

  aquire_address();

  delay(1000);//delays 100ms
}
