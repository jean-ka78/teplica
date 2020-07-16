/* 
   SimpleModbusSlaveV10 supports function 3, 6 и 16.
   serial ring buffer 64 bytes or 32 registers.
   function 3       58 bytes or 29 registers.
   function 16      54 bytes or 27 registers.
*/
#include <SimpleModbusSlave.h>



//////////////////// Макроопределения портов и настройки программы  ///////////////////
#define TxEnablePin  11	   // Tx/Rx пин RS485
#define baud         115200  // скоростьобмена по последовательному интерфейсу. (UART)
#define timeout      50  // Длительность ожидание ответа (таймаут modbus)
#define polling      300   // скорость опроса по modbus
#define retry_count  10    // количесво запросов modbus до ошибки и останова обмена
#define Slave_ID     1     // Адрес Slave устройсва
// #define LED1         13    // светодиод 1
// #define LED2         9     // светодиод 2
// const int  buttonPin = 3;     // номер входа, подключенный к кнопке
// переменные
// int buttonState = 0;         // переменная для хранения состояния кнопки
// Modbus slave(Slave_ID,1,TxEnablePin); // this is slave @1 and RS-485

#define TxEnablePin_3  0	   // Tx/Rx пин RS485
#define baud_3         115200  // скоростьобмена по последовательному интерфейсу. (UART)
#define timeout_3      1000  // Длительность ожидание ответа (таймаут modbus)
#define polling _3     300   // скорость опроса по modbus
#define retry_count_3  10    // количесво запросов modbus до ошибки и останова обмена
#define Slave_ID_3     10

// Modbus slave_1(1, 1, 11);
unsigned long tempus;
int8_t state = 0;


////////////////////////////////////////////////////////////
union float_0{
 float f;
 uint16_t u[2];
}s_data;

void io_poll() {
  // slave_data[98] = slave_1.getInCnt();
  // slave_data[99] = slave_1.getOutCnt();
  // slave_data[100] = slave_1.getErrCnt();
  slave_data[0] = reg[4];
  slave_data[1] = reg[5];
  slave_data[2] = reg[10];
  slave_data[3] = reg[11];
  slave_data[4] = reg[16];
  slave_data[5] = reg[17];
  slave_data[6] = reg[22];
  slave_data[7] = reg[23];
  slave_data[8] = reg[28];
  slave_data[9] = reg[29];
  s_data.f = Temp_in;
  // Serial.println(Temp_in);
  // Serial.println(slave_data[10]);
  slave_data[10] = s_data.u[1];
  slave_data[11] = s_data.u[0];
  s_data.f = Humid;
  slave_data[12] = s_data.u[1];
  slave_data[13] = s_data.u[0];
  s_data.f = NH3;
  slave_data[14] = s_data.u[1];
  slave_data[15] = s_data.u[0];
//   button_esp = slave_data[9];
if (slave_data[9]!=0)
{
   Serial.println("button: "+String(slave_data[9]));
}
button_esp = slave_data[10];
// Serial.print("data20: "+String(slave_data[20]));
 temp_on = slave_data[20];
// if (temp_on!=VentTempStart)
// {
//     VentTempStart = temp_on;
//     Serial.print("tempStart: "+String(slave_data[20]));
//     Serial.println(" Label: "+String(VentTempStart));
//     //  EEPROM.write(29, VentTempStart);
//     // EEPROM.end();
// }

temp_off = slave_data[21];
// if (temp_off!=VentTempStop)
// {
//     VentTempStop = temp_off;
//      Serial.print("tempstop: "+String(slave_data[21]));
//     Serial.println(" Label: "+String(VentTempStop));
//     //  EEPROM.write(30, VentTempStop);
//     // EEPROM.end();
// }

time_on = slave_data[22];
// if (time_on!=VentTime)
// {
//     VentTime = time_on;
//     //  EEPROM.write(31, VentTime);
//       Serial.print("venttime: "+String(slave_data[22]));
//     Serial.println(" Label: "+String(VentTime));
//     // EEPROM.end();
// }
//  EEPROM.end();

  

}

void slave_setup()
{
//////////////////


////////////////
    //////////
    //  slave_1.begin( baud ); // baud-rate at 19200
    //  tempus = millis() + 100; //Guarda el tiempo actual + 100ms
  //    /////////
 
   modbus_configure(&Serial1, baud, SERIAL_8N1, Slave_ID, TxEnablePin, sizeof(slave_data)/sizeof(slave_data[0]), slave_data);
  //  modbus_configure(&Serial3, baud_3, SERIAL_8N1, Slave_ID_3, TxEnablePin_3, 255, slave_data_3);

   modbus_update_comms(baud, SERIAL_8N1, Slave_ID);  
  //  modbus_update_comms(baud);  

}// конец void setup()

void slave_loop()
{
// slave_1.poll(slave_data, 100);
//  state = slave_1.poll(slave_data, 100);
//  if (state > 4) { //Si es mayor a 4 = el pedido fué correcto
//     tempus = millis() + 50; //Tiempo actual + 50ms
//     digitalWrite(13, HIGH);//Prende el led
//   Serial.print("in:"+String(slave_1.getInCnt()));
//   Serial.print(" out:"+String(slave_1.getOutCnt()));
//   Serial.println(" err:"+String(slave_1.getErrCnt()));
//   }
//   if (millis() > tempus) 

//   digitalWrite(13, LOW );//Apaga el led 50ms después
  //  io_poll();
  

  int8_t state_err = modbus_update(); // запуск обмена по Modbus
// if (state_err!= state)
// {
//   state = state_err;
//   Serial.println(" err:"+String(state));
// }

  
}// конец void loop()
