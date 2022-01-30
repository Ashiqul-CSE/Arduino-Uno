// Include all the library

#include <Wire.h>               // deals with I2C connections
//#include <LiquidCrystal_I2C.h>  // activates the LCD I2C library

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // ARDUINO UNO

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


// push button based Password protected

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
 
// your 3 digit password
int pdigit1 = 2; 
int pdigit2 = 5;
int pdigit3 = 5; 
//int pdigit4 = 9; 
 
int digit1 = 0; 
int digit2 = 0; 
int digit3 = 0; 
//int digit4 = 0; 


// MENU ARRAYS

String menuOption[] = {{"UP"}, {"Down"}, {"Cancel"}, {"Setting"}};       // Text on the top line
String measurementType[] = {{"[int]"}, {"[int]"}, {"[int]"}, {"[int]"}};  // Text on the bottom line


// PINS ON THE ARDUINO.
// MAKE THESE "CONST INT" VARIABLES AS THESE DO NOT CHANGE IN THE PROGRAM.


const int upButtonPin = 5;         // Pin 26 for "Up" command
const int downButtonPin = 6;       // Pin 28 for "Down" command
const int enterButtonPin = 12;      // Pin 30 for "Enter" command  Setting
const int clearButtonPin = 13;     // Pin 32 for "Clear" command

// NUMBER COUNT OF BUTTON PRESSES AND COUNTER UNITS.
// MAKE THESE A "INT" VARIABLES TO ALLOW FOR NEGATIVE INTEGERS.

int setting1Counter = 0;    // Counters for settings 1 - 5
int setting2Counter = 0;  
int setting3Counter = 0;
int setting4Counter = 0;
int setting5Counter = 0;
int directionPush = 0;      // This counter changes the menu option with each "left" or "right" button push.
int upPressCount = 0;       // This counter measures the amount of times the user pushes the "up" button.
int downPressCount = 0;     // This counter measures the amount of times the user pushes the "down" button.

// BUTTON PRESS STATES FOR EACH FUNCTION, ALL SET TO "LOW".
// MAKE THESE "BOOLEAN" VARIABLES AS THESE ONLY WILL BE "HIGH" OR "LOW".


boolean buttonStateUp = LOW;              // Button states for the "Up" command
boolean lastButtonStateUp = LOW;                
boolean currentButtonStateUp = LOW;
boolean buttonStateDown = LOW;            // Button states for the "Down" command
boolean lastButtonStateDown = LOW;                
boolean currentButtonStateDown = LOW; 
boolean buttonStateEnter = LOW;           // Button states for the "Enter" command
boolean lastButtonStateEnter = LOW;                
boolean currentButtonStateEnter = LOW;
boolean buttonStateClear = LOW;           // Button states for the "Clear" command
boolean lastButtonStateClear = LOW;                
boolean currentButtonStateClear = LOW;

// DEBOUNCE VARIABLES TO MEASURE THE DEBOUNCING TIME OF A BUTTON PUSH.
// MAKE THESE "UNSIGNED LONG" VARIABLES AS THE NUMERICAL VALUE WILL HAVE AN EXTENDED SIZE.

unsigned long lastDebounceTime = 0;       // This variable takes a "snapshot" of time when any button is pushed.
unsigned long debounceDelay = 50;         // Delay time in milliseconds; the amount of time the button is pressed must be higher than the delay to register a push.


// OBJECT DECLARATION
//LiquidCrystal_I2C lcd(0x27, 16, 2);   // Activates the LCD "object"


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

//  lcd.backlight();                  // THESE COMMANDS TURN ON AND CLEAR THE LCD SCREEN
//  lcd.init();
  lcd.clear();    


  pinMode(upButtonPin, INPUT);      // SETS THE upButtonPin AS AN INPUT
  pinMode(downButtonPin, INPUT);    // SETS THE downButtonPin AS AN INPUT
  pinMode(enterButtonPin, INPUT);   // SETS THE enterButtonPin AS AN INPUT
  pinMode(clearButtonPin, INPUT);   // SETS THE clearButtonPin AS AN INPUT
  
  delay(1000);

// password code

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


//* MAIN LOOP

void loop() {

// password code 

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

  int unitSetting[] = {setting1Counter, setting2Counter, setting3Counter, setting4Counter, setting5Counter};    // This variable holds the individual counters in one array
  
  lcd.setCursor(0,0);                           // Menu displayed on the LCD.
  lcd.print(menuOption[directionPush]);         // The menuOption that is displayed is determined by the left or right push.
  lcd.setCursor(0,1);    
  lcd.print(unitSetting[directionPush]);        // The setting counter that is displayed is determined by the left or right push.
  lcd.setCursor(1,1);                           // * This cursor setting fixes the measurementType in one place, preventing offset
  lcd.print(measurementType[directionPush]);    // by the unitSetting.

  // The program at this point is waiting for a button press.
  

  currentButtonStateUp = digitalRead(upButtonPin);          
  currentButtonStateDown = digitalRead(downButtonPin);    
  currentButtonStateEnter = digitalRead(enterButtonPin);
  currentButtonStateClear = digitalRead(clearButtonPin);    
  
  if (currentButtonStateUp != lastButtonStateUp || currentButtonStateDown != lastButtonStateDown || currentButtonStateEnter != lastButtonStateEnter)        
  // If there is a button push on any of the buttons, the following routine runs to check if it was a valid press: 
  {
  lastDebounceTime = millis();      // lastDebounceTime is set equal to the running millis() function.
  }  

  if ((millis() - lastDebounceTime) > debounceDelay)   
  
  // below runs and checks which button was pushed: 
  {                                             

    // The current state for each button is set not equal to the pressed state and when it changes, the pressed state becomes equal to the current state.

   
    // UP BUTTON PRESS
    if (currentButtonStateUp != buttonStateUp)           // Up button scrolls the setting upward. 
    { 
    buttonStateUp = currentButtonStateUp;  
                 
      if (buttonStateUp == LOW && directionPush == 0)    // The first 5 times in which the "up" button is pushed, each push will add 1 increment to the setting.                       
      {                
      upPressCount++;     
      downPressCount = 0;                                // The downPressCount is reset to zero.    
      setting1Counter++;

        if (upPressCount > 5)                            // If the "up" button is pushed more than 5 times consecutively, the setting increment increases by 5
        {                                                // with every "up" button push and resets back when the down, left or right button is pushed.
        setting1Counter = setting1Counter + 4;
        }

        if (setting1Counter > 255)                       // Sets the setting counter limit to 255. The user cannot increase the counter beyond 255.
        {
        setting1Counter = 255;
        }
      }  
      
      if (buttonStateUp == LOW && directionPush == 1)                         
      {            
      upPressCount++;     
      downPressCount = 0;                                             
      setting2Counter++;

        if (upPressCount > 5)
        {
        setting2Counter = setting2Counter + 4;
        }

        if (setting2Counter > 255)                       // Sets the setting counter limit to 255. The user cannot increase the counter beyond 255.
        {
        setting2Counter = 255;
        }
      }  

      if (buttonStateUp == LOW && directionPush == 2)                         
      {     
      upPressCount++;     
      downPressCount = 0;                                                     
      setting3Counter++;

        if (upPressCount > 5)
        {
        setting3Counter = setting3Counter + 4;
        }

        if (setting3Counter > 255)                       // Sets the setting counter limit to 255. The user cannot increase the counter beyond 255.
        {
        setting3Counter = 255;
        }
      }  

      if (buttonStateUp == LOW && directionPush == 3)                         
      { 
      upPressCount++;     
      downPressCount = 0;                                                         
      setting4Counter++;

        if (upPressCount > 5)
        {
        setting4Counter = setting4Counter + 4;
        }

        if (setting4Counter > 255)                       // Sets the setting counter limit to 255. The user cannot increase the counter beyond 255.
        {
        setting4Counter = 255;
        }
      }  

      if (buttonStateUp == LOW && directionPush == 4)                         
      {    
      upPressCount++;     
      downPressCount = 0;                                                      
      setting5Counter++;

        if (upPressCount > 5)
        {
        setting5Counter = setting5Counter + 4;
        }

        if (setting5Counter > 255)                       // Sets the setting counter limit to 255. The user cannot increase the counter beyond 255.
        {
        setting5Counter = 255;
        }
      }  
    lcd.clear();  
    }


    // DOWN BUTTON PRESS
    if (currentButtonStateDown != buttonStateDown)        // Down button scrolls the setting downward.
    { 
    buttonStateDown = currentButtonStateDown;  
                 
      if (buttonStateDown == LOW && directionPush == 0)   // The first 5 times in which the "down" button is pushed, each push will subtract 1 increment to the setting.                      
      {                      
      downPressCount++;
      upPressCount = 0;                                   // The upPressCount is reset to zero.
      setting1Counter--;

        if (downPressCount > 5)                           // If the "down" button is pushed more than 5 times consecutively, the setting increment decreases by 5
        {                                                 // with every "down" button push and resets back when the up, left or right button is pushed.
        setting1Counter = setting1Counter - 4;
        }

        if (setting1Counter < 0)                       // Sets the setting counter limit to 0. The user cannot increase the counter beyond 0.
        {
        setting1Counter = 0;
        }
      }  

      if (buttonStateDown == LOW && directionPush == 1)                         
      {              
      downPressCount++;
      upPressCount = 0;                                         
      setting2Counter--;

        if (downPressCount > 5)
        {
        setting2Counter = setting2Counter - 4;
        }

        if (setting2Counter < 0)                       // Sets the setting counter limit to 0. The user cannot decrease the counter beyond 0.
        {
        setting2Counter = 0;
        }
      }  

      if (buttonStateDown == LOW && directionPush == 2)                         
      {     
      downPressCount++;
      upPressCount = 0;                                                     
      setting3Counter--;

        if (downPressCount > 5)
        {
        setting3Counter = setting3Counter - 4;
        }
      
        if (setting3Counter < 0)    // This code prevents the user from entering
        {                           // a number below "0".
        setting3Counter = 0;        // Remove this code if you want to allow in
        }                           // negative numbers on a setting.    
      }  

      if (buttonStateDown == LOW && directionPush == 3)                         
      {                          
      downPressCount++;
      upPressCount = 0;                                
      setting4Counter--;

        if (downPressCount > 5)
        {
        setting4Counter = setting4Counter - 4;
        }
      
        if (setting4Counter < 0)    // This code prevents the user from entering
        {                           // a number below "0".
        setting4Counter = 0;        // Remove this code if you want to allow in
        }                           // negative numbers on a setting.
      }  

      if (buttonStateDown == LOW && directionPush == 4)                         
      {                        
      downPressCount++;
      upPressCount = 0;                                  
      setting5Counter--;

        if (downPressCount > 5)
        {
        setting5Counter = setting5Counter - 4;
        }
      
        if (setting5Counter < 0)    // This code prevents the user from entering
        {                           // a number below "0".
        setting5Counter = 0;        // Remove this code if you want to allow in
        }                           // negative numbers on a setting.
      }  
      
    lcd.clear();
    }
       
  }  
//.......................................................................................................................................................

    // ENTER BUTTON PRESS
    if (currentButtonStateEnter != buttonStateEnter)        
    { 
    buttonStateEnter = currentButtonStateEnter;  
                 
      if (buttonStateEnter == LOW && directionPush == 0)      // The Enter button simply enters the setting and flashes a brief message.                         
      {                                                       // Please feel free to expand on this code to add more functions.
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Set Password");
      lcd.setCursor(0,1);
      lcd.print("Password is Correct");
      delay(2000); 
      }  

      if (buttonStateEnter == LOW && directionPush == 1)                         
      {                                                       
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Set Low BAT");
      lcd.setCursor(0,1);
      lcd.print("Set Low Temp");
      delay(2000);
      }  

      if (buttonStateEnter == LOW && directionPush == 2)                         
      {                                                       
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Set High Temp");
      lcd.setCursor(0,1);
      lcd.print("HTP");
      delay(2000);
      }  

      if (buttonStateEnter == LOW && directionPush == 3)                         
      {                                                       
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Fan ON");
      lcd.setCursor(0,1);
      lcd.print("Duel Fan ON");
      delay(2000);
      }  

/*
      if (buttonStateEnter == LOW && directionPush == 4)                         
      {                                                       
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Duel Fan Temp");
      lcd.setCursor(0,1);
      lcd.print("Cancel");
      delay(2000);
      }  
      */
    lcd.clear();
    }


    // CLEAR BUTTON PRESS
    if (currentButtonStateClear != buttonStateClear)        
    { 
    buttonStateClear = currentButtonStateClear;  
                 
      if (buttonStateClear == LOW && directionPush == 0)    // The Clear button clears all setting data depending on what menu option you are viewing.                      
      {                                                     // It flahses a brief message stating that the data has been cleared.
      lcd.clear();                                          // The press counts for both the up and down variables are also reset to zero.
      lcd.setCursor(0,0); 
      lcd.print("Password is wrong");
      lcd.setCursor(0,1);
      lcd.print("Set new Password");
      setting1Counter = 0;
      downPressCount = 0;
      upPressCount = 0;
      delay(2000); 
      }  

      if (buttonStateClear == LOW && directionPush == 1)                         
      {                                                       
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Reset Low BAT");
      lcd.setCursor(0,1);
      lcd.print("Reset Low Temp");
      setting2Counter = 0;
      downPressCount = 0;
      upPressCount = 0;
      delay(2000);
      }  

      if (buttonStateClear == LOW && directionPush == 2)                         
      {                                                       
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Reset High Temp");
      lcd.setCursor(0,1);
      lcd.print("HTP");
      setting3Counter = 0;
      downPressCount = 0;
      upPressCount = 0;
      delay(2000);
      }  

      if (buttonStateClear == LOW && directionPush == 3)                         
      {                                                       
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Fan Off");
      lcd.setCursor(0,1);
      lcd.print("Cancel");
      setting4Counter = 0;
      downPressCount = 0;
      upPressCount = 0;
      delay(2000);
      }  

/*
      if (buttonStateClear == LOW && directionPush == 4)                         
      {                                                       
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("");
      lcd.setCursor(0,1);
      lcd.print("");
      setting5Counter = 0;
      downPressCount = 0;
      upPressCount = 0;
      delay(2000);
      }  

      */
    lcd.clear();
    }
    
   

  // After a button is pushed and the count recorded, all the states reset back to LOW for the data to be processed correctly.

  lastButtonStateUp = currentButtonStateUp;           // resets the up button state to LOW
  lastButtonStateDown = currentButtonStateDown;       // resets the down button state to LOW
  lastButtonStateEnter = currentButtonStateEnter;     // resets the enter button state to LOW
  lastButtonStateClear = currentButtonStateClear;     // resets the clear button state to LOW
  
}

// password 


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
 }

  
