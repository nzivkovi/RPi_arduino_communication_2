#include<Wire.h>

long value;
byte bytes[4];

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  value = 0;
}

void sendLong(long value){
  for(int j = 0;j < sizeof(long); j++){
    bytes[j] = value >> 8 * j;
  }
  Wire.beginTransmission(8);
  Wire.write(bytes, 4);
  Wire.endTransmission();
}

void receiveString() {
  Wire.requestFrom(8, 5);
  while(Wire.available()){
    char c = Wire.read();
    Serial.print(c);
  }
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  sendLong(++value);
  delay(1000);
  receiveString();
  delay(1000);
}
