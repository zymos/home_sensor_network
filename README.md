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

# Debug output
* RS232 via FTDI
* 2-bits
* Pins

# Arduino MiniPro
## Pinout
|Board #|#		| Def	|Bus #|Pin #|Desc|Other|
|-------|---------|-----|-----|----|----|------|
|      0|  PCINT16|  RXD|  PD0|  30|	|		|
|      1|  PCINT17|  TXD|  PD1|  31|	|		|
|      2|  PCINT18|  INT0| PD2|  32|	|		|
|      3|  PCINT19|  INT1| PD3|  1| OC2B| PWM	|
|      4|  PCINT20|  TO|   PD4|  2| XCL |		|
|      5|  PCINT21|  T1|   PD5|  9| OC0B| PWM	|
|      6|  PCINT22|  AIN0| PD6|  10|    | PWM	|
|      7|  PCINT23|  AIN1| PD7|  11|	|		|
|      8|  PCINT0|   CLK0| PB0|  12|ICP1|		|
|      9|  PCINT1|   OC1A| PB1|  13|    |  PWM	|
|      10| PCINT2|    OC2| PB2|  14|  SS|  PWM	|
|      11| PCINT3|       | PB3|  15|MOSI| PWM	|
|      12| PCINT4|       | PB4|  16|MISO|		|
|      13| PCINT5|       | PB5|  17| SCK|Built-In LED   |
|     VCC|       |    Vcc|    |  18|	|		|
|     GND|       |    GND|    |  3|		|		|
|     VCC|       |    Vcc|    |  4|		|		|
|     GND|       |   AGND|    |  5|		|		|
|     GND|       |    GND|    |  6|		|		|
|        |       |   OSC1| PB6|  7|XTAL1|[INACCESSIBLE] |
|        |       |   OSC2| PB7|  8|XTAL2|[INACCESSIBLE] |
|        |       |   ARef|    | 20|		|[INACCESSIBLE] |
|     GND|       |    GND|    | 21|		|		|
|      A6|       |       |    | 22| ADC6|		|
|      A7|       |       |    | 19| ADC7|		|
|  14(A0)| PCINT8|       | PC0| 23| ADC0|		|
|  15(A1)| PCINT9|       | PC1| 24| ADC1|		|
|  16(A2)| PCINT10|      | PC2| 25| ADC2|		|
|  17(A3)| PCINT11|      | PC3| 26| ADC3|		|
|      A4| PCINT12|      | PC4| 27| ADC4| SCL	|
|      A5| PCINT13|      | PC5| 28| ADC5| SDA	|
|        | PCINT14|      | PC6| 29|RESET| DTR	|

* https://blog.adafruit.com/wp-content/uploads/2016/07/promini_final.png

