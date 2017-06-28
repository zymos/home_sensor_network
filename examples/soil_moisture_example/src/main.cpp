/////////////////////////////////////////////////////////////////////////
//                            Sensor network
//
// Ref
//  http://www.learningaboutelectronics.com/Articles/Arduino-liquid-level-sensor-circuit.php
/////////////////////////////////////////////////////////////////////////


#include "Arduino.h"
#include "wiring_analog.c"

//#include <Narcoleptic.h> //low-power sleep


//////////////////////////////////////////////////////////////////////////
// Configuration
//////////////////////////////////////////////////////////////////////////

const uint8_t DEBUG=1; // Debug sends serial-port output


// alarm


// Pin Assignment
const uint8_t soil_moisture_pin = A2;




////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////
uint8_t count;
uint8_t relays;
uint8_t soil_moisture;



////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//// Functions
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// read adc value


void detect_soil_moisture(void){
  // Measure soil moisture Level
  soil_moisture = 255 - (analogRead(soil_moisture_pin) >> 2);
  //remove LSB to make 8-bit and invert

  if(DEBUG){
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
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
  detect_soil_moisture();
  delay(1000);
}
