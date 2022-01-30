#include <Wire.h>
//#include <TimerOne.h>
#include <LiquidCrystal_I2C.h>


#define PIN_SENSE 2 //where we connected the fan sense pin. Must be an interrupt capable pin (2 or 3 on Arduino Uno)
#define DEBOUNCE 5 //0 is fine for most fans, poor quality fans may require 10 or 20 to filter out noise
#define FANSTUCK_THRESHOLD 500 //if no interrupts were received for 500ms, consider the fan as stuck and report 0 RPM



// LCD on 0x27
LiquidCrystal_I2C lcd(0x27, 20, 4);

//Interrupt handler. Stores the timestamps of the last 2 interrupts and handles debouncing
unsigned long volatile ts1=0,ts2=0;

int potVal;
int potPin = A2;
int fanVal;
float fanSet;
//LCD Buffer
char msg[20];

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time RPM was updated

// constants won't change :
const long interval = 1000;           // interval at which to update RPM (milliseconds)


//configure Timer 1 (pins 9,10) to output 25kHz PWM
void setupTimer1(){
    //Set PWM frequency to about 25khz on pins 9,10 (timer 1 mode 10, no prescale, count to 320)
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
    TCCR1B = (1 << CS10) | (1 << WGM13);
    ICR1 = 320;
    OCR1A = 0;
    OCR1B = 0;
}

/*
//configure Timer 2 (pin 3) to output 25kHz PWM. Pin 11 will be unavailable for output in this mode
void setupTimer2(){
    //Set PWM frequency to about 25khz on pin 3 (timer 2 mode 5, prescale 8, count to 79)
    TIMSK2 = 0;
    TIFR2 = 0;
    TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B = (1 << WGM22) | (1 << CS21);
    OCR2A = 79;
    OCR2B = 0;
}
*/

//equivalent of analogWrite on pin 9
void setPWM1A(float f){
    f=f<0?0:f>1?1:f;
    OCR1A = (uint16_t)(320*f);
}

/*
//equivalent of analogWrite on pin 10
void setPWM1B(float f){
    f=f<0?0:f>1?1:f;
    OCR1B = (uint16_t)(320*f);
}
//equivalent of analogWrite on pin 3
void setPWM2(float f){
    f=f<0?0:f>1?1:f;
    OCR2B = (uint8_t)(79*f);
}
*/

void setup(){
    //enable outputs for Timer 1
    pinMode(9,OUTPUT); //1A
    //pinMode(10,OUTPUT); //1B
    setupTimer1();
    //enable outputs for Timer 2
    //pinMode(3,OUTPUT); //2
    //setupTimer2();
    //note that pin 11 will be unavailable for output in this mode!
    //example...
    //setPWM1A(0.5f); //set duty to 50% on pin 9
    //setPWM1B(0.2f); //set duty to 20% on pin 10
    //setPWM2(0.8f); //set duty to 80% on pin 3
    
    pinMode(PIN_SENSE,INPUT_PULLUP); //set the sense pin as input with pullup resistor
    attachInterrupt(digitalPinToInterrupt(PIN_SENSE),tachISR,FALLING); //set tachISR to be triggered when the signal on the sense pin goes low
  
    //initialize lcd screen
    lcd.init();
    // turn on the backlight
    lcd.backlight();

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("FAN SPEED CONTROLLER");
    lcd.setCursor(0,1);
    lcd.print("PWM DUTY: ");
    lcd.setCursor(0,2);
    lcd.print("RPM: ");
}


void loop() {
    potVal = analogRead(potPin);
    fanVal = map(potVal, 0, 1023, 0, 100);
    fanSet = float(fanVal)/100;
    setPWM1A(fanSet);
    lcd.setCursor(0,1);
    sprintf(msg, "PWM DUTY: %3d%%", fanVal);
    lcd.print(msg);

    // Non blocking delay
    // check to see if it's time to read RPM. If the difference between
    // the current time and last time you read RPM is bigger than the
    // interval, then read again.
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      // save the last time you read the RPM
      previousMillis = currentMillis;
      lcd.setCursor(0,2);
      sprintf(msg, "RPM: %4u", calcRPM());
      lcd.print(msg);
      }
}


//Calculates the RPM based on the timestamps of the last 2 interrupts. Can be called at any time.
unsigned long calcRPM(){
    if(millis()-ts2<FANSTUCK_THRESHOLD&&ts2!=0){
        return (60000/(ts2-ts1))/2;
    }else return 0;
}

void tachISR() {
    unsigned long m=millis();
    if((m-ts2)>DEBOUNCE){
        ts1=ts2;
        ts2=m;
    }
}
