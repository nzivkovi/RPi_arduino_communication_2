void spiInit() {
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE); //TURN ON SPI in slave mode
  SPCR |= _BV(SPIE); //turn on interrupts
  
}
bool sendFirst = true;
byte firstValue, secondValue;

ISR (SPI_STC_vect){
  byte c = SPDR;

  if(sendFirst){
    SPDR = firstValue;
    Serial.print("[SLAVE] - value sent ");
    Serial.print(firstValue);
  } else {
    SPDR = secondValue;
    Serial.print("[SLAVE] - value sent ");
    Serial.print(secondValue);
  }

  sendFirst = !sendFirst;
}

void setup() {
  spiInit();
  firstValue = 0;
  secondValue = 0;
  Serial.begin(115200);

}

void loop() {
  ++firstValue;
  --secondValue;
  delay(1000);

}
