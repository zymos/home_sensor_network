
//RFM69HW Blinky Code
//This program is a highly simplified version of the program by Felix from LowPowerLab
//A button is pushed on the sender unit which toggles an LED on the receiver
#include <RFM69.h>    //get it here: https://www.github.com/lowpowerlab/rfm69
#include <SPI.h>
#include <LowPower.h> //get library from: https://github.com/lowpowerlab/lowpower

//*********************************************************************************************
// *********** IMPORTANT SETTINGS - YOU MUST CHANGE/ONFIGURE TO FIT YOUR HARDWARE *************
//*********************************************************************************************
//This part of the code simply sets up the parameters we want the chip to use
// these parameters allow you to have multiple networks, channels, and encryption keys
#define NETWORKID     100  //the same on all nodes that talk to each other
#define RECEIVER      1    //unique ID of the gateway/receiver
#define SENDER        2    // you could for example, have multiple senders
#define NODEID        RECEIVER  //change to "SENDER" if this is the sender node (the one with the button)
//Select your frequency by uncommenting
#define FREQUENCY     RF69_433MHZ
//#define FREQUENCY     RF69_868MHZ
// #define FREQUENCY     RF69_915MHZ
#define ENCRYPTKEY    "sampleEncryptKey" //exactly the same 16 characters/bytes on all nodes!
#define IS_RFM69HW    //uncomment only for RFM69HW! Remove/comment if you have RFM69W!
//*********************************************************************************************
#define SERIAL_BAUD   9600

//This part defines the LED pin and button pin
#define LED             9 //LED on D9
#define BUTTON_INT      1 //user button on interrupt 1 (D3)
#define BUTTON_PIN      3 //user button on interrupt 1 (D3)
#define RX_TOGGLE_PIN   7 //GPIO to toggle on the RECEIVER

RFM69 radio;
//******** THIS IS INTERRUPT BASED DEBOUNCING FOR BUTTON ATTACHED TO D3 (INTERRUPT 1)
#define FLAG_INTERRUPT 0x01
volatile int mainEventFlags = 0;
boolean buttonPressed = false;
void handleButton()
{
mainEventFlags |= FLAG_INTERRUPT;
}
// the setup contains the start-up procedure and some useful serial data
void setup() {
Serial.begin(SERIAL_BAUD);
if(!radio.initialize(FREQUENCY,NODEID,NETWORKID)){
  Serial.println("Initializations failed");
}
#ifdef IS_RFM69HW
radio.setHighPower(); //only for RFM69HW!
#endif
radio.encrypt(ENCRYPTKEY);
char buff[50];
sprintf(buff, "\nListening at %d Mhz...", FREQUENCY==RF69_433MHZ ? 433 : FREQUENCY==RF69_868MHZ ? 868 : 915);
Serial.println(buff);
//Serial.println(readTemperature());
Serial.flush();
pinMode(BUTTON_PIN, INPUT_PULLUP);
pinMode(LED, OUTPUT);
attachInterrupt(BUTTON_INT, handleButton, FALLING);

pinMode(RX_TOGGLE_PIN, OUTPUT);

}



byte LEDSTATE=LOW; //LOW=0
void loop() {
//******** THIS IS INTERRUPT BASED DEBOUNCING FOR BUTTON ATTACHED TO D3 (INTERRUPT 1)
if (mainEventFlags & FLAG_INTERRUPT)
{
LowPower.powerDown(SLEEP_120MS, ADC_OFF, BOD_ON);
mainEventFlags &= ~FLAG_INTERRUPT;
if (!digitalRead(BUTTON_PIN)) {
buttonPressed=true;
}
}

if (buttonPressed)
{
Serial.println("Button pressed!");
buttonPressed = false;

if (radio.sendWithRetry(RECEIVER, "All About Circuits", 18)) //target node Id, message as string or byte array, message length
delay(100);

}

//check if something was received (could be an interrupt from the radio)
if (radio.receiveDone())
{
//print message received to serial
Serial.print('[');Serial.print(radio.SENDERID);Serial.print("] ");
Serial.print((char*)radio.DATA);
Serial.print("   [RX_RSSI:");Serial.print(radio.RSSI);Serial.print("]");
Serial.println();


if(LEDSTATE==LOW)
LEDSTATE=HIGH;
else LEDSTATE=LOW;
digitalWrite(LED, LEDSTATE);
digitalWrite(RX_TOGGLE_PIN, LEDSTATE);


//check if sender wanted an ACK
if (radio.ACKRequested())
{
radio.sendACK();
Serial.print(" - ACK sent");
}
}

radio.receiveDone(); //put radio in RX mode
Serial.flush(); //make sure all serial data is clocked out before sleeping the MCU
LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_ON); //sleep Arduino in low power mode (to save battery)
}
