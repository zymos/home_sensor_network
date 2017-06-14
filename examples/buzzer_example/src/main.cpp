#include <Arduino.h>
#include "Timer.h"


const uint8_t buzzer_pin = 10;                    //connect one LED to this pin (with appropriate current-limiting resistor of course)



void beep(void){
  uint16_t beep_dur=2000;
  uint16_t beep_sep=1000;
  for(uint8_t i;i<10;i++){
    tone(buzzer_pin,2400,beep_dur);
    delay(beep_dur+beep_sep);
  }
}

void setup(void)
{
    pinMode(buzzer_pin, OUTPUT);
    // t.oscillate(LED1, PERIOD1, HIGH, 10000);
    // t.oscillate(LED2, PERIOD2, HIGH);
}

void loop(void)
{
    beep();
    delay(5000);
}
