// Include all the library

#include <Wire.h>               // deals with I2C connections
#include <LiquidCrystal_I2C.h>  // activates the LCD I2C library
#include <Arduino.h>



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

int LED = 2;  // door alarm + LED


//* Password initialize keypad

int row[]={A1,A0,8,9};// Defining row pins of keypad connected to Arduino pins
int col[]={10,11,12,13};//Defining column pins of keypad connected to Arduino
int i,j,lcd_count,count=1,key_id=0,flag,entry=0;// See About the Program 
int col_scan;// Variable to identify a key press
char temp_press; // Variable to hold value of key press
char check[6],pass[6]; // See About the Program




// MENU ARRAYS

String menuOption[] = {{"UP"}, {"Down"}, {"Cancel"}, {"Setting"}};       // Text on the top line
String measurementType[] = {{"[int]"}, {"[int]"}, {"[int]"}, {"[int]"}};  // Text on the bottom line


// PINS ON THE ARDUINO.
// MAKE THESE "CONST INT" VARIABLES AS THESE DO NOT CHANGE IN THE PROGRAM.

//const int leftButtonPin = 22;       // Pin 22 for "Left" command
//const int rightButtonPin = 24;      // Pin 24 for "Right" command
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

//boolean buttonStateLeft = LOW;            // Button states for the "Left" command
//boolean lastButtonStateLeft = LOW;                
//boolean currentButtonStateLeft = LOW;
//boolean buttonStateRight = LOW;           // Button states for the "Right" command
//boolean lastButtonStateRight = LOW;                
//boolean currentButtonStateRight = LOW;
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
LiquidCrystal_I2C lcd(0x27, 16, 2);   // Activates the LCD "object"


// SETUP
void setup() {

  // * Initialize the serial port.
  
  Serial.begin(9600);

  
  

pinMode(fan1, OUTPUT);
pinMode(fan2, OUTPUT);
pinMode(temp, INPUT);
pinMode(smoke,OUTPUT );
pinMode(water, OUTPUT);
pinMode(door, OUTPUT);
pinMode(LED, OUTPUT);

  lcd.backlight();                  // THESE COMMANDS TURN ON AND CLEAR THE LCD SCREEN
//  lcd.init();
  lcd.clear();    

//  pinMode(leftButtonPin, INPUT);    // SETS THE leftButtonPin AS AN INPUT
  //pinMode(rightButtonPin, INPUT);   // SETS THE rightButtonPin AS AN INPUT
  pinMode(upButtonPin, INPUT);      // SETS THE upButtonPin AS AN INPUT
  pinMode(downButtonPin, INPUT);    // SETS THE downButtonPin AS AN INPUT
  pinMode(enterButtonPin, INPUT);   // SETS THE enterButtonPin AS AN INPUT
  pinMode(clearButtonPin, INPUT);   // SETS THE clearButtonPin AS AN INPUT
  
  delay(1000);


//* Password

  lcd.begin(16,2);
for(i=0;i<=3;i++)
{
pinMode(row[i],OUTPUT);
pinMode(col[i],INPUT);
digitalWrite(col[i],HIGH);
}
lcd.print("SET 5 Digit PASS");

}


//* MAIN LOOP

void loop() {
  

//* password loop 

 while(entry<=4)// Password Setting Loop begins
{
SetPassword();
}

// Password Setting Loop Ends

key_id=0;
keyscan(); // Scan for a Key Press

/* Actions on Key Press begins */

if(key_id==1) // Condition to Check Key is Pressed
{
 check[count]=temp_press;
count++;

/* Condition to Unlock Begins*/

if(temp_press=='A')
{
  checkPassword();
if(flag==0)
{
lcd.setCursor(0,0);
lcd.print("UNLOCKED");

}

else{ 
lcd.setCursor(0,0);
lcd.print("WRONG PASSWORD");
delay(200);
lcd.clear();
lcd.print("LOCKED");
}
count=1; // Resetting the counter variable
}

/* Condition to Unlock Ends*/

/* Condition to Change Password Begins */

else if(temp_press=='C')
{
checkPassword();
if(flag==0)
{
lcd.setCursor(0,0);
lcd.print("ENTER NEW PASS");
key_id=0;
entry=0;
}

else{ 
lcd.setCursor(0,0);
lcd.print("WRONG PASSWORD");
}
count=1; // Resetting the counter variable
}

/* Condition to Change Password Ends */

/* Condition to LOCK Begins*/

else if(temp_press=='B')
{
lcd.setCursor(0,0);
lcd.print("LOCKED");
count=1; // Resetting the counter variable
}
/* Condition to LOCK Ends*/
}


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
      
    digitalWrite(trigger,LOW);
    
    }
    Serial.println("Fan ON");
    delay(500);
  }

  else if(tempval>tempset) // 25
  {
    digitalWrite(fan1,LOW);{
      
    digitalWrite(trigger,HIGH);
    
    }
    Serial.println("Fan1 Fault");
    delay(500);
  }

  else if(tempval>tempset)  //25
  {
    digitalWrite(fan2,LOW);{
      
    
    digitalWrite(trigger,HIGH);
    
    }
    Serial.println("Fan2 Fault");
    delay(500);
  }

  else if (tempval>tempset) // 30
  {
    digitalWrite(fan1 && fan2,HIGH);{

      digitalWrite(trigger,LOW);
    }
    
   
    Serial.println("Dual Fan ON");
    delay(500);
    }

  else if (tempval<=tempset)  // 25  

 {
    digitalWrite(fan1 && fan2,LOW); {

       digitalWrite(trigger,HIGH);
    }
   
    Serial.println("Fan OFF");
    delay(500);
    }

   else if (tempval>tempset)  // 30
  {


    digitalWrite(fan1 || fan2, LOW); {
    
    digitalWrite(trigger,LOW);
    
    }
    Serial.println("Fan Fault Alarm");
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
  
//  currentButtonStateLeft = digitalRead(leftButtonPin);          
  //currentButtonStateRight = digitalRead(rightButtonPin); 
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
  // If the lastDebounceTime (aka. the "snapshot" time) minus the running millis() function is higher than the set debounce delay, the following routine
  // below runs and checks which button was pushed: 
  {                                             

    // The current state for each button is set not equal to the pressed state and when it changes, the pressed state becomes equal to the current state.
                /*
           
                 
    // LEFT BUTTON PRESS
    if (currentButtonStateLeft != buttonStateLeft)       // Left button scrolls the menu options to the left.  
    { 
    buttonStateLeft = currentButtonStateLeft;  
                 
      if (buttonStateLeft == LOW)                        // Once the button is released, the push is registered and the code below runs.
      {                                                 
      directionPush--;                                   // Both the up and down press counts will be reset to zero when the left button is pushed.
      upPressCount = 0;
      downPressCount = 0;
      }
          
        if (directionPush < 0)                           // If the user tries to scroll below the first menu option,
        {                                                // the program will loop back to the last menu option.
        directionPush = 4;
        }
    lcd.clear();    
    }

    // RIGHT BUTTON PRESS
    if (currentButtonStateRight != buttonStateRight)     // Right button scrolls the menu options to the right.    
    { 
    buttonStateRight = currentButtonStateRight;  
                 
      if (buttonStateRight == LOW)                         
      {                                                 
      directionPush++;                                   // Both the up and down press counts will be reset to zero when the right button is pushed.
      upPressCount = 0;
      downPressCount = 0;
      }
  
        if (directionPush > 4)                           // If the user tries to scroll above the last menu option,
        {                                                // the program will loop back to the first menu option.
        directionPush = 0;
        }
    lcd.clear();
    }


*/
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

        if (setting1Counter > 255)                       // Sets the setting counter limit to 999. The user cannot increase the counter beyond 999.
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

        if (setting2Counter > 255)                       // Sets the setting counter limit to 999. The user cannot increase the counter beyond 999.
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

        if (setting3Counter > 255)                       // Sets the setting counter limit to 999. The user cannot increase the counter beyond 999.
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

        if (setting4Counter > 255)                       // Sets the setting counter limit to 999. The user cannot increase the counter beyond 999.
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

        if (setting5Counter > 255)                       // Sets the setting counter limit to 999. The user cannot increase the counter beyond 999.
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

        if (setting1Counter < 0)                       // Sets the setting counter limit to -999. The user cannot increase the counter beyond -999.
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

        if (setting2Counter < 0)                       // Sets the setting counter limit to -999. The user cannot decrease the counter beyond -999.
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


    // ENTER BUTTON PRESS
    if (currentButtonStateEnter != buttonStateEnter)        
    { 
    buttonStateEnter = currentButtonStateEnter;  
                 
      if (buttonStateEnter == LOW && directionPush == 0)      // The Enter button simply enters the setting and flashes a brief message.                         
      {                                                       // Please feel free to expand on this code to add more functions.
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("DEGREES FAHREN.");
      lcd.setCursor(0,1);
      lcd.print("IS ENTERED");
      delay(2000); 
      }  

      if (buttonStateEnter == LOW && directionPush == 1)                         
      {                                                       
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("DEGREES CELSIUS");
      lcd.setCursor(0,1);
      lcd.print("IS ENTERED");
      delay(2000);
      }  

      if (buttonStateEnter == LOW && directionPush == 2)                         
      {                                                       
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("WEIGHT IN LBS.");
      lcd.setCursor(0,1);
      lcd.print("IS ENTERED");
      delay(2000);
      }  

      if (buttonStateEnter == LOW && directionPush == 3)                         
      {                                                       
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("INCHES");
      lcd.setCursor(0,1);
      lcd.print("IS ENTERED");
      delay(2000);
      }  

      if (buttonStateEnter == LOW && directionPush == 4)                         
      {                                                       
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("MILES PER HOUR");
      lcd.setCursor(0,1);
      lcd.print("IS ENTERED");
      delay(2000);
      }  
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
      lcd.print("DEGREES FAHREN.");
      lcd.setCursor(0,1);
      lcd.print("IS CLEARED");
      setting1Counter = 0;
      downPressCount = 0;
      upPressCount = 0;
      delay(2000); 
      }  

      if (buttonStateClear == LOW && directionPush == 1)                         
      {                                                       
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("DEGREES CELSIUS");
      lcd.setCursor(0,1);
      lcd.print("IS CLEARED");
      setting2Counter = 0;
      downPressCount = 0;
      upPressCount = 0;
      delay(2000);
      }  

      if (buttonStateClear == LOW && directionPush == 2)                         
      {                                                       
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("WEIGHT IN LBS.");
      lcd.setCursor(0,1);
      lcd.print("IS CLEARED");
      setting3Counter = 0;
      downPressCount = 0;
      upPressCount = 0;
      delay(2000);
      }  

      if (buttonStateClear == LOW && directionPush == 3)                         
      {                                                       
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("INCHES");
      lcd.setCursor(0,1);
      lcd.print("IS CLEARED");
      setting4Counter = 0;
      downPressCount = 0;
      upPressCount = 0;
      delay(2000);
      }  

      if (buttonStateClear == LOW && directionPush == 4)                         
      {                                                       
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("MILES PER HOUR");
      lcd.setCursor(0,1);
      lcd.print("IS CLEARED");
      setting5Counter = 0;
      downPressCount = 0;
      upPressCount = 0;
      delay(2000);
      }  
    lcd.clear();
    }
    
   

  // After a button is pushed and the count recorded, all the states reset back to LOW for the data to be processed correctly.
 // lastButtonStateLeft = currentButtonStateLeft;       // resets the left button state to LOW
  //lastButtonStateRight = currentButtonStateRight;     // resets the right button state to LOW
  lastButtonStateUp = currentButtonStateUp;           // resets the up button state to LOW
  lastButtonStateDown = currentButtonStateDown;       // resets the down button state to LOW
  lastButtonStateEnter = currentButtonStateEnter;     // resets the enter button state to LOW
  lastButtonStateClear = currentButtonStateClear;     // resets the clear button state to LOW
  
}


void SetPassword() // Subroutine to SET User Defined Password
{
keyscan();
if(key_id==1)
{
if(temp_press=='A'||temp_press=='C'||temp_press=='B') // Condition to Check for an Invalid Keypress 
{
lcd.setCursor(0,0);
lcd.print("INVALID KEYS");
entry=0;
}
else 

{
  pass[entry]=temp_press;

}
}
key_id=0;
if(entry==5)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("PASSWORD SET & LOCKED");
}
} // Subroutine to SET Password ENDS

char keyscan()// Subroutine to Scan Keypad for a Keypress
{
for(i=0; i<=3; i++)
{
digitalWrite(row[0],HIGH);
digitalWrite(row[1],HIGH);
digitalWrite(row[2],HIGH);
digitalWrite(row[3],HIGH);
digitalWrite(row[i],LOW);
for(j=0; j<=3; j++)
{
col_scan=digitalRead(col[j]);
if(col_scan==LOW)
{
  key_id=1;
  entry++;
temp_press=keypress(i,j);
lcd.setCursor(lcd_count++,1);
lcd.print(temp_press);
if(temp_press=='A'||temp_press=='C'||temp_press=='B')
{
lcd_count=0;
lcd.clear();
}
delay(300);
break;
}
}
}
}// Subroutine to Scan Keypress Ends

char keypress(int i, int j) // Subroutine to Identify the value of Key pressed
{
if(i==0&&j==0)
{
return('1');
}
if(i==0&&j==1)
{
return('2');
}
if(i==0&&j==2)
{
return('3');
}
if(i==0&&j==3)
{
return('A');
}
if(i==1&&j==0)
{
return('4');
}
if(i==1&&j==1)
{
return('5');
}
if(i==1&&j==2)
{
return('6');
}
if(i==1&&j==3)
{
return('B');
}
if(i==2&&j==0)
{
return('7');
}
if(i==2&&j==1)
{
return('8');
}
if(i==2&&j==2)
{
return('9');
}
if(i==2&&j==3)
{
return('C');
}
if(i==3&&j==0)
{
return('*');
}
if(i==3&&j==1)
{
return('0');
}
if(i==3&&j==2)
{
return('#');
}
if(i==3&&j==3)
{
return('D');
}
} // Subroutine to identify Keypress Ends

void checkPassword() // Subroutine to Check User Input Data with SET Password
{
flag=0;
for(i=1;i<=5&&flag==0;i++)
{
if(check[i]==pass[i])
{
flag=0;
}
else 
{
  flag=1;
}
}
} // Subroutine to check password ends
