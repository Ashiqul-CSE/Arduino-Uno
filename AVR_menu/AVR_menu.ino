  #include "delay.h"
  #include "button_key.h"
  #include "lcd.h"  
    
void menu_key_display(struct menu s1,const char *menu_display[]);
void UP_Down_Keyvalue(struct menu s1,int i,int j);

 /* Function Key Value For get key  */
int Key_pressed(void)
 { 
 while(1){
    if (LEFT_S) {  while(LEFT_S);return 1; }      
 if (RIGHT_S){  while(RIGHT_S);return 2; }
 if (UP_S)  {  while(UP_S); return 3; }
 if (DOWN_S) { while(DOWN_S);return 4 ; }
 if (OK_S) { while(OK_S);return 5 ; }
 } 
 } 
 
 
 /* Function Key Value For Up Key  & Enter*/
 
 void menu_key_display(struct menu s1,const char *menu_display[])
 {   
  int ch; 
   int a; 
  int  menu_position =0;
   LCD_DisplayString(menu_display[menu_position]);
            do{  
    
    repat:          
    ch = Key_pressed();
    if(ch==1||ch==2)
    {
                  if(ch==2)
                    {  if(ch==2)
                   { if(s1.menu_side_key==4)
                     s1.menu_side_key = 0;
                  LCD_Clear();
                  LCD_GoToLine(0);
                              LCD_DisplayString(*((++s1.menu_side_key)+menu_display)); 
         menu_position=1;            
         
                 } 
                      }
                   else if(ch==1)
                   {   
                             if(ch==1)
                    {if(s1.menu_side_key==1 ||s1.menu_side_key==0)
                      {
                    s1.menu_side_key=5;
                      }
                      LCD_Clear();
                            LCD_DisplayString(*((--s1.menu_side_key)+menu_display));                            
          menu_position=1;   
                         }
                   }  
          }
      
    if(menu_position==0)
    goto repat;
        }while(ch!=5);
       
        a = s1.menu_side_key; 
  switch(a)
     { 
 case 1: // set time
          { 
    LCD_Clear();
       LCD_GoToLine(0);
       LCD_DisplayString(menu_display[5]);
    LCD_GoToLine(1);
    LCD_DisplayString("  HH:MM:SS:PM/AM");
    UP_Down_Keyvalue(s1,2,4);    
          break;
          } 
 case 2: // Set date
        {
         LCD_Clear();
         LCD_GoToLine(0);
         LCD_DisplayString(menu_display[6]);
      LCD_GoToLine(1);
      LCD_DisplayString("  DD:MM:YY");
      UP_Down_Keyvalue(s1,2,3);     
         break;
        }
 
 case 3: // set alarm
          {
         LCD_Clear();
            LCD_GoToLine(0);
         LCD_DisplayString(menu_display[7]);
      LCD_GoToLine(1);
      LCD_DisplayString(" HH:MM:SS:AM/PM");
      UP_Down_Keyvalue(s1,2,4);      
          break;
             }
 case 4:  // set alarm
           {
            LCD_Clear();
          LCD_GoToLine(0);
          LCD_DisplayString(menu_display[8]);
    LCD_GoToLine(1);
    LCD_DisplayString("  HH:MM:SS:PM/AM");
    UP_Down_Keyvalue(s1,2,4);    
          break;
            }
     } 
    
  while(Key_pressed()!=5); 
  
       
 } 
 
 
 
 
 /* Function Key Value For UP_Down Key */
 void UP_Down_Keyvalue(struct menu s1,int i,int j)
 {    
  
  int ch,lower,upper;    
  do{  
    if(j==4)
     {
      if(i==2)upper=1;
      if(i==3)upper=9;
      if(i==5)upper=5;
      if(i==8)upper =5;
      if(i==9)upper =9;
     } 
      if(UP_S)   
      {
      while(UP_S);    
      if(s1.menu_up_key==upper)
      s1.menu_up_key = lower-1;
      LCD_GoToXY(1,i); 
      LCD_Printf("%d",++s1.menu_up_key);
      s1.time[i-2]=s1.menu_up_key;          
      }
   else if(DOWN_S) // down 
             
          {    while(DOWN_S);
            if (s1.menu_up_key==lower)
            s1.menu_up_key = upper+1;        
            LCD_GoToXY(1,i);
            LCD_Printf("%d",--s1.menu_up_key);
      s1.time[i-2]=s1.menu_up_key;       
     }
          if(RIGHT_S)
       
             { while(RIGHT_S);
       s1.menu_up_key=0;
          if(i==9) goto exit1;
          if(i==3||i==6)
          ++i;
          i++;
              }
      exit1:
           if (LEFT_S)
             { while(LEFT_S);
        s1.menu_up_key=0;
            if(i==2) goto exit2;         
            if(i==5||i==8)
            --i;
            i--;
     
             }
    exit2:continue;
   
   
  } while (ch!=5);  // if Okay key exit loop
  
 }
 
