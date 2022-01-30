#include <LiquidCrystal.h>

// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


//const int buzzer = 3;
const int sensor = 6;
int state; // 0 close - 1 open wwitch
void setup()
{

   lcd.begin(16, 2);

  // Clears the LCD screen
  lcd.clear();
pinMode(sensor, INPUT_PULLUP);
}
void loop()
{
state = digitalRead(sensor);
if (state == HIGH){
//tone(buzzer, 400);
lcd.print(" Door Alarm!");

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
}
else{
  lcd.print(" Door is closed!");
//noTone(buzzer);
}
delay(200);
} 
