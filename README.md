# home_sensor_network
this is a sensor network for home automations and sensor data logging

![alt text](https://github.com/zymos/home_sensor_network/raw/master/docs/images/basic_layout.gif "Block diagram")

# Sensor

* Water level sensor 
  * RB-02S048
  * Vcc = 5V
  * Output: analog
  * pins
  * http://www.learningaboutelectronics.com/Articles/Arduino-liquid-level-sensor-circuit.php
* Light sensor
  * Photoresistor + resistor voltage divider
    * Output: analog
	* pins
  * Photodiode
    * Output: analog
	* pins
* Temperature sensor
  * DS18B20
  * Vcc=5V (3.0-5.5V)
  * Output: digital 1-Wire
  * pins
  * https://www.sparkfun.com/products/245
* Temperature/Humidity sensor
  * DHT22/AM2302
  * Vcc=5V (3.3-6V)
  * Output: digital 1-Wire
  * pins
  * https://www.sparkfun.com/datasheets/Sensors/Temperature/DHT22.pdf
* Motion sensor (PIR)
  * HC-SR501
  * Vcc=5V (4.8-20V)
  * Output: Digital (3.3V)
  * pins
* Hygrometer - Soil moisture sensor
  * Vcc=5V (3-5V)
  * Output: analog
  * pins

# Relays
* 4-bit output
* pins
## Light control function
* Single relay for on/off
## Fan control function
* Three relays for low/med/high or fan1/fan2/fan3
## Animal/Pest control function
### flashing lights
* Single relay for on/off
### ultra sonics
* Single relay for on/off


# Node Address
Each address designats a location and assigns the sensors funtion.  This way a common code can be used in all sensors, with differing funtions based on address.
* 4-bit (16 locations)
* digitally assigned using jumpers, switches or soldered
* internal pullup resistors
* Pins




# RF
  
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
|Temp/Hum		|digital(i/o)	|
|Address(0)		|digital(i)		|
|Address(1)		|digital(i)		|
|Address(2)		|digital(i)		|
|Address(3)		|digital(i)		|
|Relay(0)		|digital(o)		|
|Relay(1)		|digital(o)		|
|Relay(2)		|digital(o)		|
|Relay(3)		|digital(o)		|
|Light			|analog(i)		|
|Soil Moisture	|analog(i)		|
|Water level	|analog(i)		|
|Switch(0)		|digital(i)		|
|Switch(1)		|digital(i)		|

Shift Reg - 74HC595

# Arduino MiniPro
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

* https://blog.adafruit.com/wp-content/uploads/2016/07/promini_final.png


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

