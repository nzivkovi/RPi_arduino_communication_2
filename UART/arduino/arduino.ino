void setup() {
  Serial.begin(9600);
  while(!Serial);
}

#define BUFFER_SIZE 12
byte pos = 0;
char chars[BUFFER_SIZE];

String transmittedString = "";

void loop() {
  if(Serial.available()){
    chars[pos++] = Serial.read();
  }

  if(pos == BUFFER_SIZE){
    transmittedString = String(chars);
    Serial.println(transmittedString);
    pos = 0;
  }
}
