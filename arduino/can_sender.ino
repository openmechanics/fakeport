// demo: CAN-BUS Shield, send data
#include <mcp_can.h>
#include <SPI.h>

//Pot for adjusting value
int sensorPin = A0;
int sensorValue = 0;
int cantxValue = 0;

void setup()
{
  Serial.begin(115200);
  // init can bus, baudrate: 100k
  if(CAN.begin(CAN_100KBPS) ==CAN_OK) Serial.print("can init ok!!\r\n");
  else Serial.print("Can init fail!!\r\n");
}

//Some sample CAN messages
unsigned char msg1[8] = {0, 1, 2, 3, 4, 5, 6, 7};
unsigned char msg2[8] = {0xFF, 0x01, 0x10, 0x0A, 0x00, 0x00, 0x00, 0x00};
unsigned char msg3[4] = {0xFF, 0x01, 0x10, 0x0A};


void loop()
{
  //Read the value of the pot
  sensorValue = analogRead(sensorPin);
  //Each CAN bus byte can store a value between 0-255. 
  //Dividing sensorValue by 4 puts us in that range.
  cantxValue = sensorValue / 4;
  Serial.print("cantxValue: ");
  Serial.print(cantxValue);
  Serial.println();
  //Create data packet for CAN message
  unsigned char canMsg[8] = {cantxValue, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  // send data:  id = 0x123, standrad flame, data len = 8, stmp: data buf
  CAN.sendMsgBuf(0x07B, 0, 8, canMsg);  
  delay(100);
}
