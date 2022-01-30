  #include <PinChangeInt.h>
 
#define MY_PIN 2 // we could choose any pin
 
#define MY_PIN1 3 
 
#define MY_PIN2 5 
 
#define MY_PIN3 6


int half_revolutions = 0;
int rpm = 0;
int half_revolutions2 = 0;
int rpm2 = 0;
int half_revolutions3 = 0;
int rpm3 = 0;
int half_revolutions4 = 0;
int rpm4 = 0;
volatile int state = LOW;
 
volatile int pwm_value = 0;
volatile int prev_time = 0;
uint8_t latest_interrupted_pin;
 
void rising()
{
  latest_interrupted_pin=PCintPort::arduinoPin;
  PCintPort::attachInterrupt(latest_interrupted_pin, &falling, FALLING);
  prev_time = micros();
}
 
void falling() {
  latest_interrupted_pin=PCintPort::arduinoPin;
  PCintPort::attachInterrupt(latest_interrupted_pin, &rising, RISING);
  pwm_value = micros()-prev_time;
  Serial.println(state);
}
 
void setup() {
  pinMode(MY_PIN, INPUT);
  digitalWrite(MY_PIN, HIGH);

  pinMode(MY_PIN1, INPUT);
  digitalWrite(MY_PIN1, HIGH);

  pinMode(MY_PIN2, INPUT);
  digitalWrite(MY_PIN2, HIGH);

  pinMode(MY_PIN3, INPUT);
  digitalWrite(MY_PIN3, HIGH);

  
  Serial.begin(115200);
  PCintPort::attachInterrupt(MY_PIN, &rising, RISING);
  PCintPort::attachInterrupt(MY_PIN1, &rising, RISING);
  PCintPort::attachInterrupt(MY_PIN2, &rising, RISING);
  PCintPort::attachInterrupt(MY_PIN3, &rising, RISING);
}


void loop() { 
  
  rpm = half_revolutions * 30; // Convert frecuency to RPM, note: this works for one interruption per full rotation. For two interrups per full rotation use half_revolutions * 30.
rpm2 = half_revolutions2 * 30;
rpm3 = half_revolutions3 * 30;
rpm4 = half_revolutions4 * 30;


Serial.print("RPM =\t"); //print the word "RPM" and tab.
Serial.print(rpm); // print the rpm value.
Serial.print("\n");

Serial.print("RPM2 =\t"); //print the word "RPM" and tab.
Serial.println(rpm2); // print the rpm value.
Serial.print("\n");

Serial.print("RPM3 =\t"); //print the word "RPM" and tab.
Serial.print(rpm3); // print the rpm value.
Serial.print("\n");

Serial.print("RPM4 =\t"); //print the word "RPM" and tab.
Serial.println(rpm4); // print the rpm value.
Serial.print("\n");

  }

  void rpm_fan(){
 half_revolutions++;
}
void rpm_fan2(){
 half_revolutions2++;  
}
void rpm_fan3(){
 half_revolutions3++;
}
void rpm_fan4(){
 half_revolutions4++;  
}

//void funct()
//{
  //state = !state;
//} 
