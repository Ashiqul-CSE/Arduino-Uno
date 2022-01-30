const int pulsePin = 2;
volatile unsigned long elapsed = 0;
volatile unsigned long StartTime;
volatile unsigned long StopTime;
volatile bool sawRisingEdge = false;

void setup() {
  pinMode(pulsePin, INPUT);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(pulsePin), rising, RISING);
  attachInterrupt(digitalPinToInterrupt(pulsePin), falling, FALLING);
}

void loop() {
  if (sawRisingEdge) { // Only print when a rising edge has been detected.
    sawRisingEdge = false;
    Serial.print (F("Detected rising edge at micros() = "));
    Serial.println(StartTime);
  }
  if (elapsed > 0) { // Only print when a subsequent falling edge has been detected.
    Serial.print(F("Falling edge followed "));
    noInterrupts();
    unsigned long e = elapsed; // always read >2 byte values with interrupts switched off.
    interrupts();
    Serial.print(e);
    Serial.println(F("µs later."));
    elapsed = 0;
  } 
}

void rising() {
  StartTime=micros();
  sawRisingEdge = 0;
}

void falling() {
  StopTime=micros();
  elapsed=StopTime-StartTime;
}
