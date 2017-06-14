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

const uint16_t sleep_time=1000; //ms


//////////////////////////////////////////////////////////////////////////
// Pin Assignment
//////////////////////////////////////////////////////////////////////////

// address
const uint8_t address0_pin = 5;
const uint8_t address1_pin = 6;
const uint8_t address2_pin = 7;
const uint8_t address3_pin = 8;

// PIR
const int PIR_pin= 2;

// Water Level
const uint8_t water_level_pin= A0;

// Buzzer
const uint8_t buzzer_pin = 10;

// Temperature sensor (DS18B20)
#define ONE_WIRE_BUS 4

// Temperature & Humidity sensor (DHT22)
#define DHT_pin 4

// Flasher
const uint8_t flasher_pin= 3;

// Relays
const uint8_t relay0_pin = 9;
const uint8_t relay1_pin = A0;
const uint8_t relay2_pin = A1;
const uint8_t relay3_pin = A3;

// Ceiling Fan
const uint8_t fan_relay0_pin = A0;
const uint8_t fan_relay1_pin = A1;
const uint8_t fan_relay2_pin = A3;
const uint8_t light_relay_pin = 9;







////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////
uint8_t count;
uint8_t address;
uint16_t functions;
float temperature;
uint8_t relays;
uint8_t fan;
uint8_t light;
uint8_t liquid_level;
uint8_t alarm_status;
float humidity;
dht DHT;

////////////////////////////////////////////////////////////////////////
// Initalize
////////////////////////////////////////////////////////////////////////
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress ThermometerAddress;





////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////
void aquire_address(void);

void activate_ceiling_fan(uint8_t fan, uint8_t light);  // Ceiling fan
void activate_relays(uint8_t relays); // Relays
void activate_flasher(void);        // LED Flasher
uint8_t activate_alarm(void);       // Buzzer alarm

uint8_t detect_water_level(void);   // Water level
void detect_motion(void);   //PIR
void detect_DS18B20(void);  // DS18B20 Temperature sensor
void detect_DHT22(void);    //DHT22 Temperature & Humidity

// Initializations
void init_PIR(void);
void init_water_level(void);
void init_light(void);
void init_soil(void);
void init_relay(void);
void init_flasher(void);
void init_DS18B20(void);
void init_DHT22(void);
void init_ceiling_fan(void);
void init_buzzer(void);

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
    humidity = (float)DHT.humidity;
    temperature = (float)DHT.temperature;
  }else{ //detection failed
    humidity = -1000;
    temperature = -1000;
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


void detect_motion(void) {
  //state = !state;
  while(digitalRead(PIR_pin) == HIGH){
    if (DEBUG) { Serial.println("Motion detected"); }

    // transmit motion notification

    delay(sleep_time); // recheck motion

  }

}


uint8_t detect_water_level(void){ // use water level sensor
  liquid_level = (analogRead(water_level_pin) >> 2); //remove LSB to make 8-bit
  if (DEBUG){
    Serial.print("Liquid level: ");
    Serial.println(liquid_level);//prints out liquid level sensor reading
  }
  return liquid_level;
}


void detect_DS18B20(void){
  if (DEBUG){
    Serial.println("Requesting temperatures...");
  }
  sensors.requestTemperatures();
  temperature = sensors.getTemp(ThermometerAddress);
  if(DEBUG){
    Serial.print("Temperature is: ");
    Serial.print(temperature);
    Serial.print("(Raw): ");
    Serial.print(temperature/128);
    Serial.println("C");
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


uint8_t activate_alarm(void){ // Activate alarm
  uint8_t beep_count=10;
  uint16_t beep_period=3000;
  uint16_t beep_durration=2000;
  if(liquid_level > 10){
    if (DEBUG){
      Serial.print("Alarm activatied...");
    }
    for(uint8_t i;i<beep_count;i++){
      tone(buzzer_pin,2400,beep_durration);
      delay(beep_period);
    }
    return 1;
  }else{
    return 0;
  }
}



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
    pinMode(fan_relay0_pin, OUTPUT);
    pinMode(fan_relay1_pin, OUTPUT);
    pinMode(fan_relay2_pin, OUTPUT);
    pinMode(light_relay_pin, OUTPUT);
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


////////////////////////////////////////////////
// Initalize functions
////////////////////////////////////////////////

void init_PIR(void) {
  // PIR input
  pinMode(PIR_pin, INPUT);
  // attach to interrupt
  attachInterrupt(digitalPinToInterrupt(PIR_pin), motion_detected, RISING);
}


void init_water_level(void){
  // pins assignment not needed

}
void init_light(void){
  // pins assignment not needed

}
void init_soil(void){
  // pins assignment not needed
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
  // pins
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

  // Assign pins
  pinMode(address0_pin, INPUT_PULLUP);
  pinMode(address1_pin, INPUT_PULLUP);
  pinMode(address2_pin, INPUT_PULLUP);
  pinMode(address3_pin, INPUT_PULLUP);

  // read address
  aquire_address();

  // assign function based on address
  assign_functions();
  load_function_essentials();


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

  DS18B20_sensor();
  delay(sleep_time);
}
