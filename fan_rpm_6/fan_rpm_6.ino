int rpmPins[] = {2,3}; //Choose any pins you like, any number of pins
#define NUM_RPM (sizeof(rpmPins)/sizeof(rpmPins[0])) //the number of pins is equal to the size of the pins array divided by the size of the first element
int rpmcounter[NUM_RPM];

void checkRpmPins() {
  //inspect each pin to find out if it's just gone high, then add 1 to the counter for that pin
  static bool lastPinState[NUM_RPM];
  
  for(byte i = 0; i<NUM_RPM; i++) { 
    
    if(digitalRead(rpmPins[i]) != lastPinState[i]) {
      //pin has changed from what we last saw - flip the state of our record of the pin
      lastPinState[i] = !lastPinState[i];
      
      if(lastPinState[i]) {
        //pin just went HIGH
        rpmcounter[i]++;
      }
      
    }
  }
}

void setup() {

  Serial.begin(115200);
  Serial.println("Start the program");

}

void loop() {
  static unsigned long lastmillis = 0;
  int rpm[NUM_RPM];

  checkRpmPins(); //this is the function that polls all input pins to count pulses. Call it as often as possible. Try not to skip a millisecond.

  if (millis() - lastmillis >= 1000) {

    lastmillis = millis();

    for(byte i=0; i<NUM_RPM; i++) {
      rpm[i] = rpmcounter[i]*30;
      rpmcounter[i] = 0;
    }

    for(byte i=0; i<NUM_RPM; i++) {
      Serial.print("fan");
      Serial.print(i);
      Serial.print(": ");
      Serial.print(rpm[i]);
      Serial.print("\t");
    }

    Serial.println();
  }

}
