#include<SPI.h>

const int slaveSelectPin = 10;
SPISettings settings(400000, MSBFIRST, SPI_MODE0);

byte transferByte(byte b=0x00) {
  byte c;
  SPI.beginTransaction(settings);
  digitalWrite(slaveSelectPin, LOW);
  delay(1);
  c = SPI.transfer(b);
  delay(1);  
  digitalWrite(slaveSelectPin, LOW);
  SPI.endTransaction();

  Serial.print("[MASTER] - value sent:");
  Serial.print(b);
  Serial.print("; value received: ");
  Serial.println(c);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(slaveSelectPin, OUTPUT);
  SPI.begin();
}

byte b = 0;

void loop() {
  // put your main code here, to run repeatedly:
  transferByte(--b);
  delay(10);
}
