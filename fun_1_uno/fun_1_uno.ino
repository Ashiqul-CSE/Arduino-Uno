// Library inclusion 

#include <Arduino.h>
#include "FanMonitor.h"

// *
// * Pins
// *
// initialize the variable


#define FAN_MONITOR_PIN 5

#define FAN_MONITOR_PIN1 6

#define FAN_MONITOR_PIN2 9

#define FAN_MONITOR_PIN3 10

int tempval; // temparature variable

int tempset;  // variable set temparature based 

int fan1=7;

int fan2= 8;

int temp= A0;  // analog pin temp

int smoke = 3;  // smoke

int water = 4; // water

int door = 11;  // door

int LED = 12;  // door alarm + LED


// *
// * Define the FanMonitor instance to monitor
// * the 3-wire fan.
// *
FanMonitor _fanMonitor = FanMonitor(FAN_MONITOR_PIN, FAN_TYPE_BIPOLE);
FanMonitor _fanMonitor1 = FanMonitor(FAN_MONITOR_PIN1, FAN_TYPE_BIPOLE);
FanMonitor _fanMonitor2 = FanMonitor(FAN_MONITOR_PIN2, FAN_TYPE_BIPOLE);
FanMonitor _fanMonitor3 = FanMonitor(FAN_MONITOR_PIN3, FAN_TYPE_BIPOLE);


void setup(){

 // *
  // * Initialize the serial port.
  // *
  Serial.begin(115200);

  // *
  // * Initialize the fan monitor.
  // *
  _fanMonitor.begin();
  _fanMonitor1.begin();
  _fanMonitor2.begin();
  _fanMonitor3.begin();
  

pinMode(fan1, OUTPUT);
pinMode(fan2, OUTPUT);
pinMode(temp, INPUT);
pinMode(smoke,OUTPUT );
pinMode(water, OUTPUT);
pinMode(door, OUTPUT);
pinMode(LED, OUTPUT);

}
void loop(){
 
// *
  // * Get the fan speed.
  // *
  uint16_t rpm = _fanMonitor.getSpeed();
  uint16_t rpm1 = _fanMonitor1 .getSpeed();
  uint16_t rpm2 = _fanMonitor2 .getSpeed();
  uint16_t rpm3 = _fanMonitor3 .getSpeed();

  // *
  // * Print the speed to the serial port.
  // *
  Serial.print("Fan 1 = "); 
  Serial.print(rpm); 
  Serial.println(" RPM");

  
  Serial.print("Fan 2 = "); 
  Serial.print(rpm1); 
  Serial.println(" RPM");

  
  Serial.print("Fan 3 = ");
  Serial.print(rpm2); 
  Serial.println(" RPM");

  
  Serial.print("Fan 4 = ");
  Serial.print(rpm3); 
  Serial.println(" RPM");
  
  // *
  // * Delay 1 second.
  // *
  delay(1000);

//smoke, water, door sensor logic
  
   if (smoke == HIGH)    {   
  digitalWrite(smoke, HIGH);
  Serial.println("Smoke Alarm"); {
     digitalWrite(fan1, LOW);
     digitalWrite(fan2, LOW);
    }
  delay(500);
  }

   if (water == HIGH)    {   
  digitalWrite(water, HIGH);
  Serial.println("Water Alarm");
  delay(500);
  }

   if (door == LOW)    {   
  digitalWrite(door, LOW); {
    digitalWrite(LED, HIGH);
    }
  Serial.println("Door Alarm");
  delay(500);
  }
  
//  Analog temparature value for fan fault problem

tempval=analogRead(temp);
  tempval=tempval/2.0741;


 if(tempval>tempset)  // 25c
  {
    digitalWrite(fan1,HIGH);{
      
    
    digitalWrite(rpm,HIGH);
    digitalWrite(rpm1,HIGH);
    }
    Serial.println("Fan ON");
    delay(500);
  }

  else if(tempval>tempset) // 25
  {
    digitalWrite(fan1,LOW);{
      
    digitalWrite(rpm,LOW);
    digitalWrite(rpm1,LOW);
    }
    Serial.println("Fan1 Fault");
    delay(500);
  }

  else if(tempval>tempset)  //25
  {
    digitalWrite(fan2,LOW);{
      
    
    digitalWrite(rpm2,LOW);
    digitalWrite(rpm3,LOW);
    }
    Serial.println("Fan2 Fault");
    delay(500);
  }

  else if (tempval>tempset) // 30
  {
    digitalWrite(fan1 && fan2,HIGH);{

      digitalWrite(rpm && rpm1 && rpm2 && rpm3,HIGH);
    }
    
   
    Serial.println("Dual Fan ON");
    delay(500);
    }

  else if (tempval<=tempset)  // 25  

 {
    digitalWrite(fan1 && fan2,LOW); {

       digitalWrite(rpm && rpm1 && rpm2 &&  rpm3,LOW);
    }
   
    Serial.println("Fan OFF");
    delay(500);
    }

   else if (tempval>tempset)  // 30
  {


    digitalWrite(fan1 || fan2, LOW); {
    
    digitalWrite(rpm || rpm1 || rpm2 || rpm3,LOW);
    
    }
    Serial.println("Fan Fault Alarm");
    delay(500);
     
 }
}
