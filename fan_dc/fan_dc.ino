#define F_CPU 8000000UL
#include<avr/io.h>   
#include<util/delay.h>
 
/**************************************************************************************
                                 FUNCTION DECLARATIONS
***************************************************************************************/
void Command(unsigned char cmd);
void Data(unsigned char dat);
 
/**************************************************************************************
                                 VARIABLE DECLARATIONS
***************************************************************************************/
unsigned char Array1[]="Rhydo Technology";
unsigned char Array2[]="   Cochin-17    ";
int i;
 
/**************************************************************************************
                                      MAIN FUNCTION
***************************************************************************************/
int main()
{ 
 DDRB = 0xFF;                    /* LCD data lines                                    */
 DDRD = 0X60;                    /* LCD Control lines(RS(PD5),RW(GND),EN(PD6)         */
 
 _delay_us(15);                  /* Minimum Delay To Power On LCD - Recieve Mode      */
 Command(0x30);                  /* LCD Specification Cmdmands                        */
 _delay_us(5);  
 Command(0x30);                  /* LCD Specification Commands                        */
 _delay_us(2);
 Command(0x30);                  /* LCD Specification Commands                        */
 Command(0x38);                  /* LCD Double Line Display Comdmand                  */
 Command(0x06);                  /* LCD Auto Increment Location Address Cmdmand       */
 Command(0x0C);                  /* LCD Display ON Cmdmand                            */
 Command(0x01);                  /* LCD Display Clear Cmdmand                         */
 _delay_us(1200);
 
 for(i=0;i<=16;i++)
 {
  Data(Array1[i]);               /* LCD display function                              */
 }
 Command(0xC0);                  /* LCD command for display secod raw                 */
 for(i=0;i<=16;i++)
 {
  Data(Array2[i]);               /* LCD display function                              */
 }   
 while(1); 
}
 
/***************************************************************************************
* Function    : Command
* Description : Function to send a command to LCD
* Parameters  : cmd, contains the command to be send
***************************************************************************************/
void Command(unsigned char cmd)
{
 PORTD |= 0X40;                  /* contol line RS-0(cmd register),R/W-GND(write),
                                    E-1(enable)                                       */
 PORTB  = cmd;                   /* command loaded to data port                       */
 _delay_us(50);                  /* Minimun Delay For Hold On Data                    */
 PORTD  = 0X00;                  /* contol line RS-0(cmd register),R/W-GND(write),
                                    E-0(enable)                                       */
}
/**************************************************************************************
* Function    : Data
* Description : Function to send a data to LCD
* Parameters  : dat, contains the data to be send
***************************************************************************************/
void Data(unsigned char dat)
{
PORTD |= 0X60;                   /* contol line RS-1(data register),R/W - GND(write), 
                                    E-1(enable)                                       */
PORTB  = dat;                    /* data loaded to data port                          */
_delay_us(50);                   /* Minimun Delay For Hold On Data                    */
PORTD  = 0X00;                   /* contol line RS-0(data register),R/W - GND(write), 
                                    E-0(enable)                                       */
}
