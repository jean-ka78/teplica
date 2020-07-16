#include <DS3231.h>
#include <SimpleTimer.h>
DS3231 clock;
RTCDateTime dt;
#include "Settings.h"
#include "F_EEPROM.h"

#include "ModbusMaster.h"
#include "Slave.h"
// #include "modbusSlave.h"
#include "Sensors.h"
#include "regulyator.h"
//#include <DS3232RTC.h> 
#include "encoder.h" 
#include "Lcd.h"
#include "uart.h"

const int ledPin = 13;
int ledstate = LOW;
char bufer;
unsigned long oldmillis;
unsigned long oldmillis1;
unsigned long oldmillis2;
unsigned long oldmillis3;
unsigned long oldmillis4;
unsigned long oldmillis5;
float temp;

SimpleTimer timer;


void setup() {
  slave_setup();
  Serial.begin(9600);
   //u8g.setRot180();
  Serial3.begin(115200);
  setup_uart();
  // Serial2.begin(9600);
  // button.begin();
  // enc.begin(); 
  LightSensor.begin();  
  EEPROM_READ();
  // setSetupDS18B20();
  // dht.begin();
  // pinMode(MAX485_RE_NEG, OUTPUT);
  // pinMode(MAX485_DE, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(PolivPin, OUTPUT);
  pinMode(PIN_SVET, OUTPUT);
  pinMode(RELAY1PIN, OUTPUT);
  pinMode(RELAY2PIN, OUTPUT);
  pinMode(RELAY3PIN, OUTPUT);
  pinMode(RELAY4PIN, OUTPUT);
  pinMode(RELAY_ZONA_1_PIN, OUTPUT);
  pinMode(RELAY_ZONA_2_PIN, OUTPUT);
  pinMode(RELAY_ZONA_3_PIN, OUTPUT);
  pinMode(RELAY_ZONA_4_PIN, OUTPUT);
  
  digitalWrite(ledPin, ledstate);
  digitalWrite(PolivPin, relay_poliv);
  digitalWrite(RELAY_ZONA_1_PIN, relay_Zona[0]);
  digitalWrite(RELAY_ZONA_2_PIN, relay_Zona[1]);
  digitalWrite(RELAY_ZONA_3_PIN, relay_Zona[2]);
  digitalWrite(RELAY_ZONA_4_PIN, relay_Zona[3]);

  // Init in receive mode
  // digitalWrite(MAX485_RE_NEG, 0);
  // digitalWrite(MAX485_DE, 0);
  // P16.begin(16, Serial2);
  
  analogWrite (5,60);
  // P16.preTransmission(preTransmission);
  // P16.postTransmission(postTransmission);
  
  //setSyncProvider(RTC.get); 
  // clock.begin();
  //  clock.setDateTime(__DATE__, __TIME__);
  
  setup_modbus();
 
  // timer.setInterval(50L, Sensor1); 
  // timer.setInterval(50L, zona); 
  timer.setInterval(100L, Light); 
  // timer.setInterval(400L, write_mb110); 
  // timer.setInterval(400L, read_mb110_8AC); 
  // timer.setInterval(100L, modbus_update);
  // timer.setInterval(50L, slave_loop);
  timer.setInterval(100L, telegram_8A); 
  timer.setInterval(50L, telegram_8AC);
  timer.setInterval(200L, GetMessage);
  // timer.setInterval(10000L, start);  
  // timer.setInterval(100L, SEND_DATA);  
  start();
}

void rellay(){
  if (!button_esp) {
    ledstate = LOW; digitalWrite(ledPin,ledstate);
    regs_16P[4] = ledstate;
  
  }
  
  else {
    ledstate = LOW;  digitalWrite(ledPin,ledstate);
    regs_16P[4] = ledstate;
    
   }

if (!relay_poliv) {

    digitalWrite(PolivPin, relay_poliv);
    regs_16P[2] = LOW;
  }
  
  else {
    digitalWrite(PolivPin, relay_poliv);
    regs_16P[2] = HIGH;
   }
if (!relay_svet) {

    digitalWrite(PIN_SVET, relay_svet);
    regs_16P[3]=relay_svet;
  }
  
  else {
    digitalWrite(PIN_SVET, relay_svet);
    regs_16P[3]= relay_svet;
   }
}


void loop(){
  ms=millis();
  //  unsigned long currentMillis = millis();
	    if(ms - oldmillis > 100)
	    {
	      oldmillis = ms; 
        //  telegram_8A();
        slave_loop();
        // io_poll();
      }
  timer.run();
  // zona();
   dt = clock.getDateTime();
  //  modbus_up();
 
   loop_modbus();
   io_poll();
  //  slave_loop();
   updateTemp();
   zona();
   rellay();
   uart();
//  picture_loop();
//  checkEncoder();
  
  }
