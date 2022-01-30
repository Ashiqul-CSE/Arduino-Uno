
#include <PinChangeInt.h>
int pin = 2;              //Defining interrupt pin
int pin1 = 3;
int pin2 = 5;              //Defining interrupt pin
int pin3 = 6;
volatile int state = LOW; //Variable shared in ISR

int half_revolutions = 0;
int rpm = 0;
int half_revolutions2 = 0;
int rpm2 = 0;
int half_revolutions3 = 0;
int rpm3 = 0;
int half_revolutions4 = 0;
int rpm4 = 0;
unsigned long lastmillis = 0;

void setup(){
   pinMode(2, OUTPUT);
   pinMode(3, OUTPUT);
   pinMode(5, OUTPUT);
   pinMode(6, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pin), funct, RISING); //interrupt on rising pulse on pin no 2 
   attachInterrupt(digitalPinToInterrupt(pin1), funct, RISING);
    attachInterrupt(digitalPinToInterrupt(pin2), funct, RISING); //interrupt on rising pulse on pin no 2 
   attachInterrupt(digitalPinToInterrupt(pin3), funct, RISING);
Serial.begin(9600); 
attachInterrupt(2, rpm_fan, FALLING);
attachInterrupt(3, rpm_fan2, FALLING);
attachInterrupt(5, rpm_fan3, FALLING);
attachInterrupt(6, rpm_fan4, FALLING);


}
void loop(){
   digitalWrite(2, state);            //Changing the state when interrupt is generated 
  digitalWrite(3, state); 
    digitalWrite(5, state);            //Changing the state when interrupt is generated 
  digitalWrite(6, state);
if (millis() - lastmillis == 1000){ //Uptade every one second, this will be equal to reading frecuency (Hz).
 
//detachInterrupt(2);//Disable interrupt when calculating
//detachInterrupt(3);
//detachInterrupt(5);
//detachInterrupt(6);
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

half_revolutions = 0; // Restart the RPM counter
half_revolutions2 = 0;
half_revolutions3 = 0; // Restart the RPM counter
half_revolutions4 = 0;

lastmillis = millis(); // Uptade lasmillis

attachInterrupt(2, rpm_fan, FALLING); //enable interrupt
attachInterrupt(3, rpm_fan2, FALLING);
attachInterrupt(5, rpm_fan3, FALLING);
attachInterrupt(6, rpm_fan4, FALLING);
 }
}
// this code will be executed every time the interrupt 0 (pin2) gets low.

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
void funct()
{
  state = !state;
} 
