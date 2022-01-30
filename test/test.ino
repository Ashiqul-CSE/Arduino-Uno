#include <Wire.h>               // deals with I2C connections
#include <LiquidCrystal_I2C.h>  // activates the LCD I2C library
#include <Arduino.h>


#define cellpin A1  // voltage divider calculation


// * Pins (Initialize the variable)

int tempval; // temparature variable, Analog read

int tempset;  // variable set temparature based 

int fan1=7;

int fan2= 8;

int trigger= (fan1 || fan2,LOW);  // if fan1 or fan2 is low then trigger and send fan fault alam in the display.

int temp= A0;  // analog pin temp

int smoke = 3;  // smoke

int water = 4; // water

int door = 11;  // door alarm + LED

int LED;

// voltage divider variable 

const float mvpc = 4.55;

float counts = 0;

float mv = 0;

float multiplier = 3;

float output = 0;


// OBJECT DECLARATION
LiquidCrystal_I2C lcd(0x27, 16, 2);   // Activates the LCD "object"


// SETUP
void setup() {

  // * Initialize the serial port.
  
  Serial.begin(115200);

pinMode(fan1, OUTPUT);
pinMode(fan2, OUTPUT);
pinMode(trigger, OUTPUT);
pinMode(temp, INPUT);
pinMode(smoke,OUTPUT );
pinMode(water, OUTPUT);
pinMode(door, OUTPUT);
pinMode(LED, OUTPUT);

  lcd.backlight();                  // THESE COMMANDS TURN ON AND CLEAR THE LCD SCREEN
//  lcd.init();
  lcd.clear();    
 delay(1000);
}
 void loop() {


  
// voltage divider calculations

counts = analogRead (cellpin);

mv = counts * mvpc;

output = (mv * multiplier) / 1000;

lcd.print("output v:" + String (output));
delay(1000);


  //smoke, water, door sensor logic
  
   if (smoke == HIGH)    {   
  digitalWrite(smoke, HIGH);
  lcd.print("Smoke Alarm"); {
     digitalWrite(fan1, LOW);
     digitalWrite(fan2, LOW);{
      digitalWrite(trigger, LOW);
      }
    }
  delay(500);
  }

   if (water == HIGH)    {   
  digitalWrite(water, HIGH);
  lcd.print("Water Alarm");
  delay(500);
  }

   if (door == LOW)    {   
  digitalWrite(door, LOW); {
    digitalWrite(LED, HIGH);
    }
  lcd.print("Door Alarm");
  delay(500);
  }
  
//  Analog temparature value for fan fault problem

tempval=analogRead(temp);
  tempval=tempval/2.0741;


 if(tempval>tempset)  // 25c
  {
    digitalWrite(fan1,HIGH);{
      
    digitalWrite(trigger,LOW);
    
    }
    lcd.print("Fan ON");
    delay(500);
  }

  else if(tempval>tempset) // 25
  {
    digitalWrite(fan1,LOW);{
      
    digitalWrite(trigger,HIGH);
    
    }
    lcd.print("Fan1 Fault");
    delay(500);
  }

  else if(tempval>tempset)  //25
  {
    digitalWrite(fan2,LOW);{
      
    
    digitalWrite(trigger,HIGH);
    
    }
    lcd.print("Fan2 Fault");
    delay(500);
  }

  else if (tempval>tempset) // 30
  {
    digitalWrite(fan1 && fan2,HIGH);{

      digitalWrite(trigger,LOW);
    }
    
   
    lcd.print("Dual Fan ON");
    delay(500);
    }

  else if (tempval<=tempset)  // 25  

 {
    digitalWrite(fan1 && fan2,LOW); {

       digitalWrite(trigger,HIGH);
    }
   
    lcd.print("Fan OFF");
    delay(500);
    }

   else if (tempval>tempset)  // 30
  {


    digitalWrite(fan1 || fan2, LOW); {
    
    digitalWrite(trigger,HIGH);
    
    }
    lcd.print("Fan Fault Alarm");
    delay(500);
     
 } 

 
    lcd.clear();
    }
    
   

 
  
