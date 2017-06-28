/////////////////////////////////////////////////////////////////////////
//                            Sensor network
//
// Ref
//  http://www.learningaboutelectronics.com/Articles/Arduino-liquid-level-sensor-circuit.php
/////////////////////////////////////////////////////////////////////////

#define F_CPU 16000000UL


#include "Arduino.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <dht.h>
//#include <Narcoleptic.h> //low-power sleep


//////////////////////////////////////////////////////////////////////////
// Configuration
//////////////////////////////////////////////////////////////////////////


const uint8_t DEBUG=1; // Debug sends serial-port output

const uint16_t sleep_time=1000; //ms

const uint8_t control_temperature_low = 21; // temp for fan in Celcius
const uint8_t control_temperature_med = 24; // temp for fan in Celcius
const uint8_t control_temperature_high = 27; // temp for fan in Celcius
const uint8_t control_temperature_hysteresis = 1; // temp for fan in Celcius







//////////////////////////////////////////////////////////////////////////
// Pin Assignment
//////////////////////////////////////////////////////////////////////////

// address
const uint8_t address0_pin = 5;
const uint8_t address1_pin = 6;
const uint8_t address2_pin = 7;
const uint8_t address3_pin = 8;


// Light sensor
const uint8_t light_pin = A0;
// PIR
const uint8_t PIR_pin= 3;

// Water Level
const uint8_t water_level_pin= A0;

// Soil moisture
const uint8_t soil_moisture_pin = A2;

// Buzzer
const uint8_t buzzer_pin = 10;

// Temperature sensor (DS18B20)
#define ONE_WIRE_BUS 4

// Temperature & Humidity sensor (DHT22)
#define DHT_pin 4

// Flasher
const uint8_t flasher_pin= 3;

// Ultrasonic
const uint8_t ultrasonic_pin= 3;

// Relays
const uint8_t relay0_pin = A0;
const uint8_t relay1_pin = A1;
const uint8_t relay2_pin = A2;
const uint8_t relay3_pin = A3;

// Ceiling Fan
const uint8_t fan_relay0_pin = A1; // low
const uint8_t fan_relay1_pin = A2; // med
const uint8_t fan_relay2_pin = A3; // high
const uint8_t light_relay_pin = A0; // light

// Switches
const uint8_t switch_light_pin = 9;
const uint8_t switch_fan_pin = A0;

// LED outputs
const uint8_t LED0_pin = 9;
const uint8_t LED1_pin = 9;
const uint8_t LED2_pin = 9;
const uint8_t LED3_pin = 9;
const uint8_t LED4_pin = 9;




////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////
uint8_t count; // used in DEBUG, to count loops
uint8_t address; // location 0-15
uint16_t functions;

int8_t temperature; // Sensor measurement from DHT22 or DS18B20
int8_t humidity; // sensor measurement from DHT22

uint8_t relays;
uint8_t ceiling_fan_status;
uint8_t ceiling_light_status;
uint8_t soil_moisture;
uint8_t liquid_level;
uint8_t alarm_status;


uint8_t alarm; // buzzer on/off

// PIR motion sensor vars
uint8_t motion_detected;
uint8_t motion_count;

// Light level
uint8_t light_level;





////////////////////////////////////////////////////////////////////////
// Initalize
////////////////////////////////////////////////////////////////////////
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress ThermometerAddress;
dht DHT;




////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////
void aquire_address(void);



void activate_flasher(void);        // LED Flasher
void activate_alarm(void);       // Buzzer alarm




// Initializations
void init_flasher(void);
void init_buzzer(void);

// Light level
void detect_light(void);

// Soil moisture
void init_soil(void);
void detect_soil_moisture(void);  // Soil moisture

// Water level
void init_water_level(void);
void detect_water_level(void);   // Water level

// Relays
void activate_relays(uint8_t relays); // Relays
void init_relay(void);

// Ceiling fan
void init_ceiling_fan(void);
void activate_ceiling_fan(uint8_t fan, uint8_t light);  // Ceiling fan

// Temperature & Humidity
void init_DS18B20(void);
void init_DHT22(void);
void detect_DS18B20(void);  // DS18B20 Temperature sensor
void detect_DHT22(void);    //DHT22 Temperature & Humidity

// PIR motion sensor
void motion_started(void);
void motion_stoped(void);
void detect_motion(void);









////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//// Functions
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////





////////////////////////////////////////////
// Detection functions
////////////////////////////////////////////


void detect_DHT22(void){
  // DHT22 sensor
  // measures Temperature & Humidity
  int chk = DHT.read22(DHT_pin);

  if(chk == DHTLIB_OK){ // detection successful
    humidity = (int8_t)DHT.humidity;
    temperature = (int8_t)DHT.temperature;
  }else{ //detection failed
    humidity = -127;
    temperature = -127;
  }

  if(DEBUG){
      switch (chk){
      case DHTLIB_OK:
          Serial.print("DHT22 humidity: ");
          Serial.print(humidity, 1);
          Serial.print("\% \nDHT22 temperature: ");
          Serial.print(temperature, 1);
          Serial.println("C");
          break;
      case DHTLIB_ERROR_CHECKSUM:
          Serial.print("DHT22: Checksum error,\n");
          break;
      case DHTLIB_ERROR_TIMEOUT:
          Serial.print("DHT22: Time out error,\n");
          break;
      case DHTLIB_ERROR_CONNECT:
          Serial.print("DHT22: Connect error,\n");
          break;
      case DHTLIB_ERROR_ACK_L:
          Serial.print("DHT22: Ack Low error,\n");
          break;
      case DHTLIB_ERROR_ACK_H:
          Serial.print("DHT22: Ack High error,\n");
          break;
      default:
          Serial.print("DHT22: Unknown error,\n");
          break;
      }
    }
}



void detect_water_level(void){
  // Measure water level
  liquid_level = (analogRead(water_level_pin) >> 2); //remove LSB to make 8-bit
  if (DEBUG){
    Serial.print("Liquid level: ");
    Serial.println(liquid_level);//prints out liquid level sensor reading
  }
}



void detect_soil_moisture(void){
  // Measure soil moisture Level
  soil_moisture = 255 - (analogRead(soil_moisture_pin) >> 2); //remove LSB to make 8-bit;
  //soil_moisture = adc_read(0);
  if(DEBUG){
    Serial.print("Soil Moisture: ");
    Serial.println(soil_moisture);
  }
}



void detect_DS18B20(void){
  if (DEBUG){Serial.println("Requesting temperatures...");}
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

void detect_light(void){
  light_level = analogRead(light_pin) >> 2; // inverts and makes it 8-bit
  if(DEBUG){
    Serial.print("Light level: ");
    Serial.println(light_level);
  }
}

////////////////////////////////////////////////
// Activation functions
////////////////////////////////////////////////

void activate_flasher(void){
  uint16_t led_on_time=100;
  uint16_t led_off_time=100;
  uint16_t led_settle_time=1000;
  if(DEBUG){
    Serial.println("Flashing lights");
  }
  digitalWrite(flasher_pin, HIGH); // LED on 1
  delay(led_on_time);
  digitalWrite(flasher_pin, LOW); // LED off
  delay(led_off_time);
  digitalWrite(flasher_pin, HIGH); // LED on 2
  delay(led_on_time);
  digitalWrite(flasher_pin, LOW); // LED off
  delay(led_settle_time);
}


void activate_alarm(void){ // Activate alarm
  uint8_t beep_count=10;
  uint16_t beep_period=3000;
  uint16_t beep_durration=2000;
  while(liquid_level > 10){
    if (DEBUG){
      Serial.print("Alarm activatied...");
    }
    alarm = 1;
    for(uint8_t i;i<beep_count;i++){
      tone(buzzer_pin,2400,beep_durration);
      delay(beep_period);
    }
  }
  alarm = 0;
}




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




/////////////////////////////////////////////
// Other functions
/////////////////////////////////////////////

void aquire_address(void){
  // Assign pins
  pinMode(address0_pin, INPUT_PULLUP);
  pinMode(address1_pin, INPUT_PULLUP);
  pinMode(address2_pin, INPUT_PULLUP);
  pinMode(address3_pin, INPUT_PULLUP);

  // Read pins for address
  address = 0xff;
  address |= digitalRead(address3_pin); // reads into first digit
  address <<= 1; // shifts
  address |= digitalRead(address2_pin); // reads into first digit
  address <<= 1;// shifts
  address |= digitalRead(address1_pin);// reads into first digit
  address <<= 1;  // shifts
  address |= digitalRead(address0_pin);// reads into first digit
  address = ~address; // Pull up resistors means inverted
  if (DEBUG){
    Serial.print("Address(bin) is: ");
    Serial.print(not(digitalRead(address3_pin)));
    Serial.print(not(digitalRead(address2_pin)));
    Serial.print(not(digitalRead(address1_pin)));
    Serial.println(not(digitalRead(address0_pin)));
    Serial.print("Address is: ");
    Serial.println(address);
  }
}



void display_functions(void){
	if(functions & 0x8000){
		Serial.println("Function 0x8000: NULL active");
	}
	if(functions & 0x4000){
		Serial.println("Function 0x4000: NULL active");
	}
	if(functions & 0x2000){
		Serial.println("Function 0x2000: NULL active");
	}
	if(functions & 0x1000){
		Serial.println("Function 0x1000: RF active");
	}
	if(functions & 0x0800){
		Serial.println("Function 0x0800: Ceiling fan active");
	}
	if(functions & 0x0400){
		Serial.println("Function 0x0400: Relay active");
	}
	if(functions & 0x0200){
		Serial.println("Function 0x0200: Ultrasonic active");
	}
	if(functions & 0x0100){
		Serial.println("Function 0x0100: Bed active");
	}
	if(functions & 0x0080){
		Serial.println("Function 0x0080: PIR active");
	}
	if(functions & 0x0040){
		Serial.println("Function 0x0040: Soil active");
	}
	if(functions & 0x0020){
		Serial.println("Function 0x0020: Water level active");
	}
	if(functions & 0x0010){
		Serial.println("Function 0x0010: Buzzer active");
	}
	if(functions & 0x0008){
		Serial.println("Function 0x0008: Flasher active");
	}
	if(functions & 0x0004){
		Serial.println("Function 0x0004: Light level active");
	}
	if(functions & 0x0002){
		Serial.println("Function 0x0002: Temperature & Humidity (DHT22) active");
	}
	if(functions & 0x0001){
		Serial.println("Function 0x0001: Temperature (DS18B20) active");
	}

}

void load_function_essentials(void){
  // runs setups for each function
  if(functions & 0x8000){
		// unassigned
	}
	if(functions & 0x4000){
		// unassigned
	}
	if(functions & 0x2000){
		// unassigned
	}
	if(functions & 0x1000){
		// RF
	}
	if(functions & 0x0800){
		// Ceiling fan

	}
	if(functions & 0x0400){
		// Relay
	}
	if(functions & 0x0200){
		// Ultrasonic
	}
	if(functions & 0x0100){
		// Bed
	}
	if(functions & 0x0080){
		// PIR
	}
	if(functions & 0x0040){
		// Soil
	}
	if(functions & 0x0020){
		// Water level
	}
	if(functions & 0x0010){
		// Buzzer
	}
	if(functions & 0x0008){
		// Flasher
	}
	if(functions & 0x0004){
		// Light level
	}
	if(functions & 0x0002){
		// Temperature & Humidity (DHT22)
	}
	if(functions & 0x0001){
		// Temperature (DS18B20)
	}
}


void assign_functions(void){
  // Posible Functions
  //
  //  [0x8000]  -
  //  [0x4000]  -
  //  [0x2000]  -
  //  [0x1000]  - RF
  //  [0x0800]  - CF  - Ceiling fan
  //  [0x0400]  - R   - Relay
  //  [0x0200]  - U   - Ultrasonic
  //  [0x0100]  - B   - Bed
  //  [0x0080]  - PIR
  //  [0x0040]  - S   - Soil
  //  [0x0020]  - W   - Water level
  //  [0x0010]  - BZ  - Buzzer
  //  [0x0008]  - F   - Flasher
  //  [0x0004]  - L   - Light level
  //  [0x0002]  - TH  - Temperature & Humidity (DHT22)
  //  [0x0001]  - T   - Temperature (DS18B20)

  if(address == 0){ //sensor 1
    // RF, CF, T
      functions = 0b0001100000000001;
  }


  if(DEBUG){display_functions();};
}


void preform_actions(void){
  if(address == 0){
    // sensor location: Bedroom ceiling fan

  }
}

////////////////////////////////////////////////
// Initalize functions
////////////////////////////////////////////////


void initialize_functions(void){
  if(address == 0){
    // sensor location: Bedroom ceiling fan
    // Sensors
    init_DS18B20();
    // Actions
    init_ceiling_fan();
  }
}


void init_PIR(void){
  pinMode(PIR_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIR_pin), detect_motion, RISING);
}



void init_water_level(void){
  // nothing needed
}
void init_light(void){
  // nothing needed
}
void init_soil_moisture(void){
  // nothing needed
}

void init_relay(void){
  // pins
  pinMode(relay0_pin, OUTPUT);
  pinMode(relay1_pin, OUTPUT);
  pinMode(relay2_pin, OUTPUT);
  pinMode(relay3_pin, OUTPUT);
}

void init_flasher(void){
  // pins
  pinMode(flasher_pin, OUTPUT);
}


void init_DS18B20(void){
  // pins
  sensors.begin();
  sensors.getAddress(ThermometerAddress, 0);
}

void init_DHT22(void){
  // nothing needed
}

void init_ceiling_fan(void){
  // pins
  pinMode(fan_relay0_pin, OUTPUT);
  pinMode(fan_relay1_pin, OUTPUT);
  pinMode(fan_relay2_pin, OUTPUT);
  pinMode(light_relay_pin, OUTPUT);
}


void init_buzzer(void){
  // pins
  pinMode(buzzer_pin, OUTPUT);
}

void init_ultrasonic(void){
  // pin
  pinMode(ultrasonic_pin, OUTPUT);
}

void init_LED0(void){
  // pin
  pinMode(LED0_pin, OUTPUT);
}

void init_LED1(void){
  // pin
  pinMode(LED1_pin, OUTPUT);
}

void init_LED2(void){
  // pin
  pinMode(LED2_pin, OUTPUT);
}

void init_LED3(void){
  // pin
  pinMode(LED3_pin, OUTPUT);
}

void init_LED4(void){
  // pin
  pinMode(LED4_pin, OUTPUT);
}

void switch_fan(void) {
  // pin
  pinMode(switch_fan_pin, INPUT_PULLUP);
}

////////////////////////////////////////
// Sensors
////////////////////////////////////////

void sensor_main_bedroom_ceiling_fan(void){
  // Sensors: DS18B20
  // Actions: ceiling fan(fan, light)

  // Loop 5m{
  //    Read temperature
  //    transmit temperature

  // wait for reciever
  // preform action
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

  // read address
  aquire_address();

  // assign function based on address
  init_DS18B20();
  init_ceiling_fan();
  init_PIR();

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

  detect_DHT22();
  detect_DS18B20();
  detect_light();
  detect_soil_moisture();
  detect_water_level();

  control_ceiling_fan();
  //activate_relays();

  activate_alarm();
  activate_flasher();

  delay(sleep_time);
}
