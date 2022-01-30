const int hallPin = 9;     // hall effect sensor out pin
const int ledPin =  13;    // LED pin

int hallState = 0;         // Initial hall sensor status

void setup() {
  
  pinMode(ledPin, OUTPUT); // LED pin as an output     
  
  pinMode(hallPin, INPUT); // The hall effect sensor pin as an input   
}

void loop(){
  
  hallState = digitalRead(hallPin); // reading the state of the hall effect sensor pin

  if (hallState == LOW) {     
    
    digitalWrite(ledPin, HIGH);  // turn LED on     
  } 
  else {
    
    digitalWrite(ledPin, LOW);  // turn LED off
  }
}
