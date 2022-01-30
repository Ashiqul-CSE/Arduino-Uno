#include<LiquidCrystal.h>  
LiquidCrystal lcd(7,6,5,4,3,2); 
int row[]={A1,A0,8,9};// Defining row pins of keypad connected to Arduino pins
int col[]={10,11,12,13};//Defining column pins of keypad connected to Arduino
int i,j,lcd_count,count=1,key_id=0,flag,entry=0;// See About the Program 
int col_scan;// Variable to identify a key press
char temp_press; // Variable to hold value of key press
char check[6],pass[6]; // See About the Program

void setup()
{
lcd.begin(16,2);
for(i=0;i<=3;i++)
{
pinMode(row[i],OUTPUT);
pinMode(col[i],INPUT);
digitalWrite(col[i],HIGH);
}
lcd.print("SET 5 Digit PASS");
}

/* Main Program Begins */

void loop()
{ 
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

}else{ 
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
}else{ 
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

/* Actions on Key Press Ends*/
}

/* Main Program Ends */


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
}} // Subroutine to SET Password ENDS

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
}}
}}// Subroutine to Scan Keypress Ends

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
{flag=1;
}}} // Subroutine to check password ends
