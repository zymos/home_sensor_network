//
//    FILE: dht22_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.03
// PURPOSE: DHT library test sketch for DHT22 && Arduino
//     URL:
// HISTORY:
// 0.1.03 extended stats for all errors
// 0.1.02 added counters for error-regression testing.
// 0.1.01
// 0.1.00 initial version
//
// Released to the public domain
//

#include <dht.h>

uint8_t DEBUG=1;

// pins
#define DHT_pin 4


/////////////////////////////////////////
//  Variables
/////////////////////////////////////////
int8_t temperature;
int8_t humidity;
dht DHT;




/////////////////////////////////////////
// Functions
/////////////////////////////////////////

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


void setup()
{
    Serial.begin(9600);

}

void loop()
{
    // READ DATA

    detect_DHT22();

    delay(1000);
}
