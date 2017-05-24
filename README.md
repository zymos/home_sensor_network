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
* 3-bit output
* 3 function modes
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
* 5-bit 
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
