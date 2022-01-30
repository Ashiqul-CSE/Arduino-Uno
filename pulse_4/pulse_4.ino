#include <PinChangeInt.h>
 
#define MY_PIN 5 // we could choose any pin
 
volatile int pwm_value = 0;
volatile int prev_time = 0;
volatile int state = LOW;
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
  pinMode(MY_PIN, INPUT); digitalWrite(MY_PIN, HIGH);
  Serial.begin(115200);
  PCintPort::attachInterrupt(MY_PIN, &rising, RISING);
}
 
void loop() { }
