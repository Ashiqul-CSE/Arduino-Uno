#include <LiquidCrystal.h>


#define rs 6 // original 12 of arduino
#define en 7 // origional 10
#define d4 8  // original 5
#define d5 9 // 4
#define d6 10 // 3
#define d7 11 // 2
// rw of lcd is connected to ground


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// Tracks the time since last event fired
unsigned long previousMillis=0;
unsigned long int previoussecs = 0; 
unsigned long int currentsecs = 0; 
 unsigned long currentMillis = 0; 

 int secs = 0; 
 

int interval= 1 ; // updated every 1 second
int epass = 2; // enter password 
int load1 = 13; // the output load/ machine, it can be a bulb, a motor etc ...
int rbutton = 3; // reset button
 
int Lflag = 0; // load flag
 
// your 4 digit password
int pdigit1 = 2; 
int pdigit2 = 5;
int pdigit3 = 5; 
//int pdigit4 = 9; 
 
int digit1 = 0; 
int digit2 = 0; 
int digit3 = 0; 
//int digit4 = 0; 


void setup()
{
    Serial.begin(9600);
    // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.clear();
  lcd.print("Password  select"); 
      // Initialise the IO and ISR
pinMode(epass, INPUT_PULLUP);
pinMode(rbutton, INPUT_PULLUP);


pinMode(load1, OUTPUT); 
digitalWrite(load1, LOW);


delay(1000);

}


void loop()
{

   currentMillis = millis();
   currentsecs = currentMillis / 1000; 
    if ((unsigned long)(currentsecs - previoussecs) >= interval) 
    {
      secs = secs + 1;
      previoussecs = currentsecs;
      if (secs >= 10)
      {
        secs = 0; 
      }
 lcd.setCursor(12,1);
 lcd.print(secs); 
    }           

    password();

  if (digitalRead(rbutton) == LOW )
  {
    digitalWrite(load1, LOW); 
    Lflag == 0; 
    digit1 = 0;
    digit2 = 0 ;
    digit3 = 0; 
    //digit4 = 0; 
    Serial.println("reset"); 
    lcd.setCursor(0,1);
    lcd.print("    ");

    delay(1000); 
  }
}    


 void password()
 {
 if ( (secs >= 1) && ( digitalRead(epass) == LOW) && (digit1 == 0) && (digit2 == 0) && (digit3 == 0) )
  {
    digit1 = secs; 
    Serial.println(digit1);
    lcd.setCursor(0,1);
    lcd.print("*"); 
    delay(500); 
  }
// for digit2
   if ( (secs >= 1) && ( digitalRead(epass) == LOW) && (digit1 != 0) && (digit2 == 0) && (digit3 == 0) )
  {
    digit2 = secs; 
    Serial.println(digit2);
    lcd.setCursor(1,1);
    lcd.print("*");
    delay(500);
  }

  // for digit3
   if ( (secs >= 1) && ( digitalRead(epass) == LOW) && (digit1 != 0) && (digit2 != 0) && (digit3 == 0))
  {
    digit3 = secs;
    Serial.println(digit3); 
    lcd.setCursor(2,1);
    lcd.print("*");
    delay(500);
  }

    // for digit3
 /*  if ( (secs >= 1) && ( digitalRead(epass) == LOW) && (digit1 != 0) && (digit2 != 0) && (digit3 != 0) && (digit4 ==0))
  {
    digit4 = secs; 
    Serial.println(digit4);
    lcd.setCursor(3,1);
    lcd.print("*");
    delay(500);
  }
*/

    if ( (pdigit1 == digit1) && ( pdigit2 == digit2) && (pdigit3 == digit3) && (Lflag == 0) ) 
    {
      digitalWrite(load1, HIGH);  
      Lflag == 1; 
    }
  
 }

 
