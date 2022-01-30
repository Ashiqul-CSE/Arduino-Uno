#include <Servo.h>
Servo myservo; 
const int EnTxPin = 2;
void setup () {
  Serial.begin (9600);
  myservo.attach (9); 
  pinMode(EnTxPin, OUTPUT );
  digitalWrite (EnTxPin, LOW );
}

void loop (){
  if ( Serial.available ()){
    if ( Serial.read () == 'I' ){
      char function = Serial.read ();
      if (function == 'S' ){
        int angle = Serial.parseInt ();
        if ( Serial.read () == 'F' ){
          if (angle <= 180) {
            myservo.write (angle);
          }
        }
      }
      else if (function == 'L' ){
        if ( Serial.read () == 'F' ){
          int val = analogRead (0);
          digitalWrite (EnTxPin, HIGH ); //enable to transmit
          Serial.print ( "i" ); 
          Serial.print (val); 
          Serial.println ( "f" ); 
          Serial.flush (); 
          digitalWrite (EnTxPin, LOW ); //enable to receive
        }
      }
    }
  }
  delay (10);
}
