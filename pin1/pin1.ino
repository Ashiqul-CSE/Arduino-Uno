#include <PinChangeInt.h>
int pin = 2;              //Defining interrupt pin
int pin1 = 3;
volatile int state = LOW; //Variable shared in ISR

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pin), funct, RISING); //interrupt on rising pulse on pin no 2 
   attachInterrupt(digitalPinToInterrupt(pin1), funct, RISING);
  // put your setup code here, to run once:

}

void loop() {
  digitalWrite(13, state);            //Changing the state when interrupt is generated 
  digitalWrite(12, state); 
  // put your main code here, to run repeatedly:

}

void funct()
{
  state = !state;
} 
