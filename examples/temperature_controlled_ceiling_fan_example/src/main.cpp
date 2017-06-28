/////////////////////////////////////////////////////////////////////////
//                            Sensor network
//
// Ref
//  http://www.learningaboutelectronics.com/Articles/Arduino-liquid-level-sensor-circuit.php
/////////////////////////////////////////////////////////////////////////


#include "Arduino.h"
#include <OneWire.h>
#include <DallasTemperature.h>

//#include <Narcoleptic.h> //low-power sleep


//////////////////////////////////////////////////////////////////////////
// Configuration
//////////////////////////////////////////////////////////////////////////

const uint8_t DEBUG=1; // Debug sends serial-port output

const uint16_t sleep_time=2000; //ms

const uint8_t control_temperature_low = 21;
const uint8_t control_temperature_med = 24;
const uint8_t control_temperature_high = 27;
const uint8_t control_temperature_hysteresis = 1;

//////////////////////////////////////////////////////////////////////////
// Pin Assignment
//////////////////////////////////////////////////////////////////////////


// Temperature sensor (DS18B20)
#define ONE_WIRE_BUS 4

// Ceiling Fan
const uint8_t fan_relay0_pin = A1; // low
const uint8_t fan_relay1_pin = A2; // med
const uint8_t fan_relay2_pin = A3; // high
const uint8_t light_relay_pin = A0; // light





////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////
uint8_t count;

int8_t temperature; // signed int, 7 bit resolution: -127 to 127
uint8_t relays;
uint8_t ceiling_fan_status;
uint8_t ceiling_light_status;


////////////////////////////////////////////////////////////////////////
// Initalize
////////////////////////////////////////////////////////////////////////
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress ThermometerAddress;





////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////
void detect_DS18B20(void);
void init_ceiling_fan(void);
void init_DS18B20(void);
void activate_ceiling_fan(uint8_t fan_change, uint8_t light_change);







////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//// Functions
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////



////////////////////////////////////////
// Sensors
////////////////////////////////////////

void control_ceiling_fan(void){
  // detect temperature
  detect_DS18B20();

  // ignore unrealistice temperatures
  if(temperature < -20 || temperature > 50){
      if(DEBUG){Serial.println("Error: temperature value is unrealistic, no change");}
      return;
  }
  if(DEBUG){
    Serial.print("Fan status:");
    Serial.print(ceiling_fan_status);
    if(ceiling_fan_status == 0x00){
      if(DEBUG){Serial.println(", off");}
    }else if(ceiling_fan_status & 0x01){
      if(DEBUG){Serial.println(", low");}
    }else if(ceiling_fan_status & 0x02){
      if(DEBUG){Serial.println(", med");}
    }else if(ceiling_fan_status & 0x04){
      if(DEBUG){Serial.println(", high");}
    }else{
      Serial.println(", ERROR not valid");
    }
  }
  // Change fan status
  if(ceiling_fan_status == 0){ // fan is currently off
      if(temperature >= control_temperature_high){
        activate_ceiling_fan(4, 0);
      }else{ if(temperature >= control_temperature_med){
        activate_ceiling_fan(2, 0);
      }else{ if(temperature >= (control_temperature_low + control_temperature_hysteresis)){
        activate_ceiling_fan(1, 0);
      }}}
  }else if(ceiling_fan_status == 1){ // fan is currently low
      if(temperature <= control_temperature_low - control_temperature_hysteresis){
        activate_ceiling_fan(0, 0); // turning off
      }else if(temperature >= control_temperature_high){
        activate_ceiling_fan(4, 0); // turn high
      }else if(temperature >= control_temperature_med + control_temperature_hysteresis){
        activate_ceiling_fan(2, 0); // turn med
      }
  }else if(ceiling_fan_status == 2){ //fan is currently med
      if(temperature <= control_temperature_low){
        activate_ceiling_fan(0, 0); // turn off
      }else if(temperature <= control_temperature_med - control_temperature_hysteresis){
        activate_ceiling_fan(1, 0); // turn low
      }else if(temperature >= control_temperature_high + control_temperature_hysteresis){
        activate_ceiling_fan(4, 0); // turn high
      }
  }else if(ceiling_fan_status == 4){ // fan is currently high
      if(temperature <= control_temperature_low ){
        activate_ceiling_fan(0, 0); // turn off
      }else if(temperature <= control_temperature_med){
        activate_ceiling_fan(1, 0); // turn low
      }else if(temperature <= control_temperature_high - control_temperature_hysteresis){
        activate_ceiling_fan(2, 0); // turn med
      }
  }
}


void activate_ceiling_fan(uint8_t fan_change, uint8_t light_change){
  // exclusive relay activation for fan_change
  // non-exclusive relay activation for light
  if(DEBUG){
    Serial.print("Fan state change: ");
    Serial.print(ceiling_fan_status);
    Serial.print(" to ");
    Serial.println(fan_change);
  }

  // Light Bulb
  if(light_change){
    digitalWrite(light_relay_pin, HIGH);
    if(DEBUG){Serial.println("Ceiling light: on");}
  }else{
    digitalWrite(light_relay_pin, LOW);
    if(DEBUG){Serial.println("Ceiling light: off");}
  }
  ceiling_light_status = light_change; // set global

  // Ceiling fan
  if(fan_change != 0x00 && fan_change != 0x01 && fan_change != 0x02 && fan_change != 0x04){
    // make sure multiple fan_change coils are nor powered
    if(DEBUG){
      Serial.print("ERROR: fan_change var=");
      Serial.print(fan_change);
      Serial.println(": fan_change relay is not exclusive or is nonsesical, keeping previous settings\n");
    }
    return;
  }
  // Low speed
  if(fan_change & 0x01){
    digitalWrite(fan_relay0_pin, HIGH);
    if(DEBUG){Serial.println("Fan Relay 0, low: on");}
  }else{
    digitalWrite(fan_relay0_pin, LOW);
    if(DEBUG){Serial.println("Fan Relay 0, low: off");}
  }
  // Med speed
  if(fan_change & 0x02){
    digitalWrite(fan_relay1_pin, HIGH);
    if(DEBUG){Serial.println("Fan Relay 1, med: on");}
  }else{
    digitalWrite(fan_relay1_pin, LOW);
    if(DEBUG){Serial.println("Fan Relay 1, med: off");}
  }
  // High speed
  if(fan_change & 0x04){
    digitalWrite(fan_relay2_pin, HIGH);
    if(DEBUG){Serial.println("Fan Relay 2, high: on");}
  }else{
    digitalWrite(fan_relay2_pin, LOW);
    if(DEBUG){Serial.println("Fan Relay 2, high: off");}
  }
  if(DEBUG){Serial.println("");}

  ceiling_fan_status = fan_change; //set global
}



void detect_DS18B20(void){
  if (DEBUG){
    Serial.println("Requesting temperatures...");
  }
  sensors.requestTemperatures();

  //temperature is in degrees Celcius from -64 to +64
  temperature = sensors.getTemp(ThermometerAddress)>>7;

  if(DEBUG){
    Serial.print("Temperature is: ");
    Serial.print(temperature);
    Serial.print("(int C): ");
    Serial.print(float(sensors.getTemp(ThermometerAddress))/128);
    Serial.println("(float C)");
  }
}


void init_DS18B20(void){
  // pins
  sensors.begin();
  sensors.getAddress(ThermometerAddress, 0);
}


void init_ceiling_fan(void){
  // pins
  pinMode(fan_relay0_pin, OUTPUT);
  pinMode(fan_relay1_pin, OUTPUT);
  pinMode(fan_relay2_pin, OUTPUT);
  pinMode(light_relay_pin, OUTPUT);
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

  init_DS18B20();
  init_ceiling_fan();

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

  control_ceiling_fan();

  delay(sleep_time);
}
