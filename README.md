# home_sensor_network
this is a sensor network for home automations and sensor data logging

![alt text](https://github.com/zymos/home_sensor_network/raw/master/docs/images/basic_layout.gif "Block diagram")




|Node ID |Location					|Abbreviation	|	
---------------------------------------------
| 0x00	| Crawl Space Front			| CSF	|
| 0x01	| Crawl Space Back			| CSB	|
| 0x02	| Main Bedroom Light Switch	| MBLS	|
| 0x03	| Main Bedroom Ceiling Fan	| MBCF	|
| 0x04	| Main Bedroom Window		| MBW	|
| 0x05	| Computer Room Window		| CRW	|
| 0x06	| Computer Room Light Switch| CRLS	|
| 0x07	| Computer Room Ceiling Fan	| CRCF	|
| 0x08	| Main Bathroom				| Bath	|
| 0x09	| Kitchen					| Kit	|
| 0x0A	| Living Room				| LR	|
| 0x0B	| Washing Room				| WR	|
| 0x0C	| Front Yard				| FY	|
| 0x0D	| Back Yard					| BY	|
| 0x0E	| Side Walk					| SW	|
| 0x0F	| Garden					| Gard	|


|Peripheral ID|Function		| Notes		|
-----------------------------------------
| 0x00		| Temperature	|DS18B20	|
| 0x01		| Temperature&Humidity	|DHT22	|
| 0x02		| Motion		| PIR		|
| 0x03		| Light Level	|
| 0x04		| Water Level	|
| 0x05		| Soil Moisture	|
| 0x06		| Bed Ocupancy	|
| 0x07		|				|
---------------------------------------
| 0x10		| Lamp			|
| 0x11		| Fan Low		|
| 0x12		| Fan Med		|
| 0x13		| Fan High		|
| 0x14		| Flasher		|
| 0x15		| Ultrasonic	|
| 0x16		| Buzzer	|
| 0x17		|			|
---------------------------------------
| 0x20		| Relay 0	|
| 0x21		| Relay 1	|
| 0x22		| Relay 2	|
| 0x23		| Relay 3	|
| 0x24		|			|
| 0x30		| Switch 0	|
| 0x31		| Switch 1	|
| 0x32		| Switch 2	|
| 0x33		| Switch 3	|
| 0x34		|			|
| 0x40		| LED 0		|
| 0x41		| LED 1		|
| 0x42		| LED 2		|
| 0x43		| LED 3		|
| 0x44		| LED 4		|
| 0x45		| LED 5		|
| 0x46		| 			|


# Inputs
|Location	|Address	|Bed	|Soil	|W	|RFrx	|L	|TH		|T	|SWL	|SWF	| SW0	| SW1	|
|-----------|-----------|-------|-------|---|-------|---|-------|---|-------|-------|-------|-------|
| FCS		| 0			| X		| 1		| X	| X		| X	| 1		| x	| x		| x		| x		| x		|
| BCS		| 1			| X		| 1		| X	| X		| X	| 1		| x	| x		| x		| x		| x		|
| MBR CF	| 2			| X		| X		| X	| X		| X	| X		| x	| x		| x		| x		| x		|
| MBR CP	| 3			| x		| x		| x	| 1		| 1	| x		| 1 | 1		| 1		| 1		| 1		|


# Outputs
|Location	|Address	|F	|U	|CFL |CF1 |CF2 |CF3 |R0	|R1	|R2	|R3	|RFtx |LED0|LED1|LED2|LED3|LED4|
|-----------|-----------|---|---|----|----|----|----|---|---|---|---|-----|----|----|----|----|----|
| FCS		| 0			| 1	| 1	| X	 | X  | X  | x  | x	| x	| x	|x	| 1	  | x  | x  | x  | x  | x  |
| BCS		| 1			| 1	| x	| X	 | X  | X  | x  | x	| x	| x	|x 	| 1   | x  | x  | x  | x  | x  |
| MBR CF	| 2			| X	| X	| 1	 | 1  | 1  | 1  | x	| x	| x	|x  | 1   | 1  | 1  | 1  | 1  | x  |

* Location abbriviations
	* _MBR CF = Main Bedroom ceiling fan_
	* _MBR CP = Main bedroom control panel_
	* _FCS = Front crawl space_
	* _BCS = Back crawl space_

* Input abbriviations
	* _Bed = bed occupency sensor_
	* _Soil = soil moisture sensor_
	* _W = Water level sensor_
	* _RFrx = Radio transiever (Rx)_
	* _L = Light level_
	* _TH = Temperature and Humidity sensor, DHT22_
	* _T = Temperature sensor, DS18B20_
	* _SWL = Switch light_
	* _SWF = Switch Fan mode_
	* _SW0 = Switch 0_

* Outputs abbrivaiations
	* _F = Flasher_
	* _U = Ultrasonic_
	* _CFL = Ceiling fan light_
	* _CF1 = Ceiling fan low_
	* _CF2 = Ceiling fan med_
	* _CF3 = Ceiling fan high_
	* _R0 = Relay 0_
	* _R1 = Relay 1_
	* _R2 = Relay 2_
	* _R3 = Relay 3_
	* _RFtx = Radio transmit_
	* _LED0 = LED light_
	* _LED1 = LED fan mode, auto_
	* _LED2 = LED fan mode, low_
	* _LED3 = LED fan mode, med_
	* _LED4 = LED fan mode, high_



* Water level sensor 
  * RB-02S048
  * Vcc = 5V
  * Output: analog
  * pins
  * http://www.learningaboutelectronics.com/Articles/Arduino-liquid-level-sensor-circuit.php
* Light sensor
![alt text](https://github.com/zymos/home_sensor_network/raw/master/schematics/light_sensor_schem.jpg "Light sensor")
  * Photoresistor + resistor voltage divider
    * Output: analog
	* pins
  * Photodiode
    * Output: analog
	* pins
* Temperature sensor
![alt text](https://github.com/zymos/home_sensor_network/raw/master/schematics/temperature_sensor-DS18B20_schem.jpg "Temp sensor")
  * DS18B20
  * Vcc=5V (3.0-5.5V)
  * Output: digital 1-Wire
  * pins
  * https://www.sparkfun.com/products/245
* Temperature/Humidity sensor
![alt text](https://github.com/zymos/home_sensor_network/raw/master/schematics/temperature_humidity_sensor-DHT22_schem.jpgl "Temperature/Humidity sensor")
  * DHT22/AM2302
  * Vcc=5V (3.3-6V)
  * Output: digital 1-Wire
  * pins
  * https://www.sparkfun.com/datasheets/Sensors/Temperature/DHT22.pdf
* Motion sensor (PIR)
![alt text](https://github.com/zymos/home_sensor_network/raw/master/schematics/PIR_360_degrees_sensor_schem.jpg "PIR")
  * HC-SR501
  * Vcc=5V (4.8-20V)
  * Output: Digital (3.3V)
  * pins
* Hygrometer - Soil moisture sensor
![alt text](https://github.com/zymos/home_sensor_network/raw/master/schematics/soil_moisture_sensor_schem.jpg "Hygrometer")
  * Sunkee soil hygrometer
  * Vcc=5V (3-5V)
  * Output: analog
  * pins
* Bed occupancy sensor
	* -
	* https://www.openhardware.io/view/65/Bed-Occupancy-Sensor

# Relays
* 4-bit output
* pins
## Light control function
* Single relay for on/off
## Fan control function
![alt text](https://github.com/zymos/home_sensor_network/raw/master/schematics/relay_array-ceilling_fan_schem.jpg "Ceiling fan")
* Three relays for low/med/high or fan1/fan2/fan3
## Animal/Pest control function
### flashing lights
* Single relay for on/off
### ultra sonics
* Single relay for on/off


# Alarm
* 390-0004-Z
** Piezo Buzzer, 150Ohm
** from a UPS
** http:// www.e-gizmo.com/PRODUCT/pdf/buzzers%20and%20speakers.pdf


# Node Address
Each address designats a location and assigns the sensors funtion.  This way a common code can be used in all sensors, with differing funtions based on address.
* 4-bit (16 locations)
* digitally assigned using jumpers, switches or soldered
* internal pullup resistors
* Pins




# RF
![alt text](https://github.com/zymos/home_sensor_network/raw/master/schematics/RFM69-radio_schem.jpg "RF")

* Transeiver
  * RFM69HW
  * Vcc=3.3V
  * Pins
  * www.hoperf.com/upload/rf/RFM69HW-V1.3.pdf
  * https://learn.sparkfun.com/tutorials/rfm69hcw-hookup-guide
  * https://github.com/LowPowerLab/RFM69
  * https://github.com/sparkfun/RFM69HCW_Breakout/

|Board Label |Name |Function|
|------------|-----|--------|
|3.3V |Power |3.3V power supply (at least 130 mA, see below)|
|G / GND |Ground |Power ground|
|O / MISO |Master In Slave Out |Data from RFM69HCW to microcontroller|
|I / MOSI |Master Out Slave In |Data from microcontroller to RFM69HCW|
|C / SCK |Serial ClocK |Clock signal from microcontroller to RFM69HCW|
|S / NSS |Slave Select |Select signal from microcontroller to RFM69HCW|
|0 / DIO0 |Digital I/O 0|
|RX interrupt |Received data ready interrupt signal from RFM69HCW to microcontroller|
|A / ANT |Antenna |Wire antenna, see the next page for details|
|G / GND |Ground |Antenna ground (same as power ground)|



# Debug output
* RS232 via FTDI
* 2-bits
* Pins


# Sensor I/O
|Pin			|Type			|Type											|
|---------------|---------------|-----------------------------------------------|
|Debug(Rx)		|digital(i)		|
|Debug(Tx)		|digital(o)		|
|RF(0)			|				|Requires 3.3V level converter					|
|RF(s)			|				|Requires 3.3V level converter					|
|RF(i)			|				|Requires 3.3V level converter					|
|RF(c)			|				|Requires 3.3V level converter					|
|RF(o)			|				|Requires 3.3V level converter					|
|PIR(0)			|digital(i)		|All PIRs are in parallel and take only one pin	|
|PIR(1)			|digital(i)		|All PIRs are in parallel and take only one pin	|
|PIR(2)			|digital(i)		|All PIRs are in parallel and take only one pin	|
|PIR(3)			|digital(i)		|All PIRs are in parallel and take only one pin	|
|Temp/Hum		|digital(i/o)	| OneWire interface
|Address(0)		|digital(i)		| Pull-up
|Address(1)		|digital(i)		| Pull-up
|Address(2)		|digital(i)		| Pull-up
|Address(3)		|digital(i)		| Pull-up
|Relay(0)		|digital(o)		| 
|Relay(1)		|digital(o)		|
|Relay(2)		|digital(o)		|
|Relay(3)		|digital(o)		|
|Light			|analog(i)		| Value=80-255 of 255
|Soil Moisture	|analog(i)		|
|Water level	|analog(i)		|
|Switch(0)		|digital(i)		| Pull-up
|Switch(1)		|digital(i)		| Pull-up


Shift Reg - 74HC595



# Arduino MiniPro
![alt text](https://github.com/zymos/home_sensor_network/raw/master/schematics/MCU-arduino_pro_mini_schem.jpg "MCU")

## Pinout
|Board #|PinChangeInt|Def|Bus #|Pin #|Notes 1|Notes 2|Sensor Assign|Assign		|
|-------|-----------|-------|----|----|-----|-------|-------------|-------------|
|      0|  PCINT16	|  RXD	| PD0|  30|		|			| Debug(Rx)	| Serial	|
|      1|  PCINT17	|  TXD	| PD1|  31|		|			| Debug(Tx)	| Serial	|
|      2|  PCINT18	|  INT0	| PD2|  32|		|			| RF(0)		| RFM69		|
|      3|  PCINT19	|  INT1	| PD3|  1 | OC2B| PWM		| PIR		| Digital(i)|
|      4|  PCINT20	|  TO	| PD4|  2 | XCL |			| Tempature	| 			|
|      5|  PCINT21	|  T1	| PD5|  9 | OC0B| PWM		| Address(0)| Digital(i)|
|      6|  PCINT22	|  AIN0	| PD6|  10|    	| PWM		| Address(1)| Digital(i)|
|      7|  PCINT23	|  AIN1	| PD7|  11|		|			| Address(2)| Digital(i)|
|      8|  PCINT0	|   CLK0| PB0|  12|ICP1	|			| Address(3)| Digital(i)|
|      9|  PCINT1	|   OC1A| PB1|  13|    	|  PWM		| Relay(0)	| Digital(o)|
|      10| PCINT2	|    OC2| PB2|  14|  SS	|  PWM		| RF(S)		| RFM69		|
|      11| PCINT3	|       | PB3|  15|MOSI	| PWM		| RF(I)		| RFM69		|
|      12| PCINT4	|       | PB4|  16|MISO	|			| RF(O)	  	| RFM69		|
|      13| PCINT5	|       | PB5|  17| SCK	|Built-In LED| RF(C)	| RFM69		|
|     VCC|       	|    Vcc|    |  18|		|			| xxxx		| xxxx		|
|     GND|       	|    GND|    |  3 |		|			| xxxx		| xxxx		|
|     VCC|       	|    Vcc|    |  4 |		|			| xxxx		| xxxx		|
|     GND|       	|   AGND|    |  5 |		|			| xxxx		| xxxx		|
|     GND|       	|    GND|    |  6 |		|			| xxxx		| xxxx		|
|        |       	|   OSC1| PB6|  7 |XTAL1|[INACCESSIBLE] |xxxx	| xxxx		|
|        |       	|   OSC2| PB7|  8 |XTAL2|[INACCESSIBLE] |xxxx	| xxxx		|
|        |       	|   ARef|    | 20|		|[INACCESSIBLE] |xxxx	| xxxx		|
|     GND|       	|    GND|    | 21|		|			| xxxx		| xxxx		|
|      A6|       	|       |    | 22| ADC6	|			| Light 	| Analog(i) |
|      A7|       	|       |    | 19| ADC7	|			| Water 	| Analog(i) |
|  14(A0)| PCINT8	|       | PC0| 23| ADC0	|			| Relay(1)	| Digital(o)|
|  15(A1)| PCINT9	|       | PC1| 24| ADC1	|			| Relay(2)	| Digital(o)|
|  16(A2)| PCINT10	|      	| PC2| 25| ADC2	|			| Soil		| Analog In	|
|  17(A3)| PCINT11	|      	| PC3| 26| ADC3	|			| Relay(3)	| Digital(o)|
|      A4| PCINT12	|      	| PC4| 27| ADC4	| SCL		| Switch 0	| Digital(i)|
|      A5| PCINT13	|      	| PC5| 28| ADC5	| SDA		| Switch 1	| Digital(i)|
|        | PCINT14	|      	| PC6| 29|RESET	| DTR		| Reset		| xxxx		|

| Pin Name | Type	|
---------------------
| address0 |	Digital INPUT PULL_UP
| address1 |	Digital INPUT PULL_UP 
| address2 |	Digital INPUT PULL_UP
| address3 |	Digital INPUT PULL_UP
| PIR			| digital INPUT
| water_level	| analog INPUT
| soil_moisture	| analog INPUT
| buzzer		| Digital INPUT
| flasher		| Digital INPUT 
| ultrasonic	| Digital INPUT 
| switch0 |	Digital INPUT PULL_UP
| switch1 |	Digital INPUT PULL_UP
| switch2 |	Digital INPUT PULL_UP
| switch3 |	Digital INPUT PULL_UP
| LED0 |	Digital OUPUT
| LED1 |	Digital OUPUT
| LED2 |	Digital OUPUT
| LED3 |	Digital OUPUT
| LED4 |	Digital OUPUT
| RFM69_SS | Digital SPI
| RFM69_SCLK | Digital SPI
| RFM69_MISO | Digital SPI
| RFM69_MOSI | Digital SPI

*New assignments
|Pin #	|Assignments|Notes|
|-------|-----------|-----|
|      0|  Debug(Rx)|
|      1|  Debug(Tx)|
|      2|  |
|      3| PIR(motion_detected) |
|      4| DHT22/DS18B20(temperature/humidity) |
|      5| Address3		| SW8	|
|      6| Address2  	| SW4	|
|      7| Address1 		| SW2	|
|      8| Address0 		| SW1	|
|      9|  |
|      10| |
|      11| |
|      12| |
|      13| |
|      A6| |
|      A7| |
|  14(A0)| Relay0/CF(light_relay)	|
|  15(A1)| Relay1/CF(fan_relay0) |
|  16(A2)| Relay2/CF(fan_relay1) |
|  17(A3)| Relay4/CF(fan_relay2) |
|      A4| |
|      A5| |


* https://blog.adafruit.com/wp-content/uploads/2016/07/promini_final.png

# 3.3V Regulator
![alt text](https://github.com/zymos/home_sensor_network/raw/master/schematics/3.3V-Regulator_schem.jpg "3.3V LDO")

# Sensors

### Crawl space sensor 1
* Location: Front crawl space
* Node address: 0
* Sensors
  * Temp/Humit
  * Soil moisture
  * PIR
* Relays
  * Flashing LED

### Crawl space sensor 1
* Location: Back crawl space
* Node address: 1
* Sensors
  * Temp/Humit
  * Soil moisture
  * PIR
* Relays
  * Flashing LED
  * Ultrasonic


### Main Bedroom
* Location: Main Bedroom
* Node address: 2
* Sensors
  * Temperature
  * Light
  * PIR
* Relays
  * Light
  * Fan low
  * Fan med
  * Fan high


### Main Bedroom Window
* Location: Main Bedroom window
* Node address: 3
* Sensors
  * Temperature
  * Light
  * PIR
* Relays
  * Fan 1
  * Fan 2
  * Fan 3
 


### Computer Room
* Location: Computer Room
* Node address: 4
* Sensors
  * Temperature
  * Light
  * PIR
* Relays
  * Light
  * Fan low
  * Fan med
  * Fan high


### Computer Room Window
* Location: Computer Room Window
* Node address: 5
* Sensors
  * Temperature
  * Light
* Relays
  * Fan low
  * Fan high
  * Fan 2

### Main Bathroom
* Location: main bathroom
* Node address: 6
* Sensors
  * Temperature
  * Light
  * PIR
* Relays
  * Light
  * Fan

### Main Bedroom's Bed
* Location: main bathroom's bed
* Node address: 6
* Sensors
  * Temperature

### Kitchen
* Location: Kitchen
* Node address: 7
* Sensors
  * Temperature
  * Light
  * PIR
* Relays
  * Light
  * Fan

### Living Room
* Location: living room
* Node address: 8
* Sensors
  * Temperature
  * Light
  * PIR
  * Button interface
* Relays
  * Light
  * Fan
* LED status


### Washing machine room
* Location: washing machine room
* Node address: 9
* Sensors
  * Temperature
  * Light
  * PIR
  * Water level
* Relays
  * Light
  * Fan
* Audio alarm


### Front yard
* Location: front yard
* Node address: 10
* Sensors
  * Temperature
  * Light


### Back yard
* Location: back yard
* Node address: 11
* Sensors
  * Temperature
  * Light


### Side walk
* Location: side walk
* Node address: 12
* Sensors
  * Temperature
  * Light
  * PIR
  * Soil moisture
* Relays
  * Light


### Garden
* Location: garden
* Node address: 13
* Sensors
  * Temperature
  * Light
  * Soil moisture


# Libraries
* [RFM69](https://github.com/LowPowerLab/RFM69)
* [LowPower](https://github.com/lowpowerlab/lowpower) - sleep
* [OneWire](https://github.com/PaulStoffregen/OneWire) - DS18b20
* [DHT.h](https://learn.adafruit.com/dht?view=all) - https://github.com/adafruit/DHT-sensor-library - integrated


# References
* https://lowpowerlab.com/guide/gateway/ DIY Home Automation System Moteino+Rasberry Pi
* [Soil Hygrometer - Instructables](http://www.instructables.com/id/How-to-Use-the-Soil-Hygrometer-Module-Arduino-Tuto/)
* [Soil Hygrometer - Spark Fun](https://learn.sparkfun.com/tutorials/soil-moisture-sensor-hookup-guide)
* [Photoresistor - Arduino](https://playground.arduino.cc/Learning/PhotoResistor)
* [PIR - Adadruit](https://learn.adafruit.com/pir-passive-infrared-proximity-motion-sensor?view=all)
* [Water level sensor - Instructables](http://www.instructables.com/id/How-to-use-a-Water-Level-Sensor-Arduino-Tutorial/)

