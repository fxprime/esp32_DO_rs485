/* -------------------------------------------------------------------------- */
/*                   ModuleMore RS-LDO-N01-1 (Modbus) Example code            */
/* -------------------------------------------------------------------------- */

/* ------------------------------- วิธีการต่อ ------------------------------- */
/**
| ESP32 | 12V Adapter | MAX485 | DO RS485 |
|-------|-------------|--------|----------|
| GND   | GND         | GND    | Black    |
| 3.3V  |             | VCC    |          |
|       | 12V         |        | Brown    |
| 4     |             |RE & DE |          |
| 18    |             | RO     |          |
| 19    |             | DI     |          |
|       |             | A      | Yellow   |
|       |             | B      | Blue     |
 **/

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ModbusMaster.h>

EspSoftwareSerial::UART mySerial;

#define MAX485_DE 4
#define MAX485_RE 4
#define MAX485_RO 18
#define MAX485_DI 19

ModbusMaster node;

void preTransmission() { digitalWrite(MAX485_DE, 1); }
void postTransmission() { digitalWrite(MAX485_DE, 0); }
float convertRegistersToFloat(uint16_t reg0, uint16_t reg1);

void setup()
{
  Serial.begin(115200);

  while (!Serial)
    ;

  Serial.println("Hi!");

  // กำหนดขาที่่ต่อกับ DE ให้เป็น Output
  pinMode(MAX485_DE, OUTPUT);
  // ตั้งค่าเริ่มต้นให้เป็นโหมดรอรับสัญญาณ
  digitalWrite(MAX485_DE, 0);

  Serial.println("start init serial 0");

  // กำหนด baudrate สำหรับสื่อสารกับ DO sensor ที่ค่าเริ่มต้นคือ 4800
  Serial.println("start init software serial");
  mySerial.begin(4800, EspSoftwareSerial::SWSERIAL_8N1, MAX485_RO, MAX485_DI, false, 95, 11);

  // กำหนด Address ที่ 1 โดยใช้ช่องทางสื่อสารผ่าน mySerial ที่เรากำหนดไว้
  node.begin(1, mySerial);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
  Serial.println("start++");
}

void loop()
{
  uint8_t result;
  uint16_t data[2];

  Serial.printf("Collect data on id %d\n", 1);
  result = node.readHoldingRegisters(0x00, 6);
  if (result == node.ku8MBSuccess)
  {
    // Get DO saturation (registers 0-1)
    float do_saturation = convertRegistersToFloat(node.getResponseBuffer(0), node.getResponseBuffer(1));
    
    // Get DO concentration (registers 2-3)
    float do_concentration = convertRegistersToFloat(node.getResponseBuffer(2), node.getResponseBuffer(3));
    
    // Get temperature (registers 4-5)
    float temperature = convertRegistersToFloat(node.getResponseBuffer(4), node.getResponseBuffer(5));
    
    // Print out the values
    Serial.println(" - Success");
    Serial.print("DO Saturation: ");
    Serial.print(do_saturation, 2);
    Serial.println(" %");
    
    Serial.print("DO Concentration: ");
    Serial.print(do_concentration, 2);
    Serial.println(" mg/L");
    
    Serial.print("Temperature: ");
    Serial.print(temperature, 2);
    Serial.println(" °C");
  }
  else
  {
    Serial.println(" - failed");
  }
  delay(50);
}



float convertRegistersToFloat(uint16_t reg0, uint16_t reg1) {
  union {
    uint8_t b[4];
    float f;
  } converter;
  
  // Correct byte order for big-endian to little-endian conversion
  converter.b[3] = (reg0 >> 8) & 0xFF;  // MSB of first register
  converter.b[2] = reg0 & 0xFF;         // LSB of first register
  converter.b[1] = (reg1 >> 8) & 0xFF;  // MSB of second register
  converter.b[0] = reg1 & 0xFF;         // LSB of second register
  
  return converter.f;
}