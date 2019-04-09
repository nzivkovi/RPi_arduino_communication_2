void spiInit() {
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE); // turn on SPI in slave mode
  SPCR |= _BV(SPIE); // turn on interrupts
}

byte b;

ISR (SPI_STC_vect) {
  byte c = SPDR;
  SPDR = b;
  Serial.print("[SLAVE] - value sent: ");
  Serial.print(b);
  Serial.print("[SLAVE] - value received: ");
  Serial.println(c);
}

void setup() {
  // put your setup code here, to run once:
  spiInit();
  b = 0;
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  ++b;
  delay(1000);
}
