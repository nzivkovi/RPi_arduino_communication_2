#include<Wire.h>

void setup() {
  // put your setup code here, to run once:
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

long received[4];
long value;
void receiveEvent(int i){
  unsigned char index = 0;
  while(Wire.available()){
    received[index++] = Wire.read();
  }
  value = 0;
  for(int j = 0; j < sizeof(long); ++j){
    value += received[j] << 8 * j;
  }
  Serial.println(value);
}

void requestEvent(){
  Wire.write("Hello");
}
