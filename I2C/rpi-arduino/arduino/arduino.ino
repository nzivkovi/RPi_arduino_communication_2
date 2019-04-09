#include <Wire.h>

const byte slaveAddr = 0x44;

long dataSent, dataReceived;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Wire.begin(slaveAddr);

  Wire.onReceive(receiveLong);
  Wire.onRequest(sendLong);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void receiveLong(int i) {
  long bytes[sizeof(long)];
  byte index = 0;
  while(Wire.available())
    bytes[index++] = Wire.read();

  dataReceived = 0;
  for(int j = 0;j< sizeof(long); ++j)
    dataReceived += bytes[j] << j * 8;
  Serial.println(dataReceived);
}

void sendLong() {
  dataSent = 1646846;
  byte bytes[sizeof(long)];
  for(int j = 0; j < sizeof(long);++j)
    bytes[j] = dataSent >> j * 8;
  Wire.write(bytes, 4);
  Serial.println(dataSent);
}
