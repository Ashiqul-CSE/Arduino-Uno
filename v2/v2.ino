volatile int counter = 0;
volatile int result = 0;
volatile int led = 13;
void setup() {
 cli();
 TCCR1A = 0;
 TCCR1B = 0;
 TCNT1 = 0;
 OCR1A = 15624; //(16*10^6) / (1024 * 1) -1
 TCCR1B |= (1 << WGM12);
 TCCR1B |= (1 << CS12) | (1 >> CS10);
 TIMSK1 |= (1 << OCIE1A);
 sei();
 pinMode(led, OUTPUT);
 attachInterrupt(0,rpm,RISING);
 Serial.begin(9600);
 }
ISR(TIMER1_COMPA_vect) {
 result = (counter / 2) * 60;
 counter = 0;
 } 
void rpm() {
 counter++;
 }
void loop() {
 Serial.println(result);
 }
