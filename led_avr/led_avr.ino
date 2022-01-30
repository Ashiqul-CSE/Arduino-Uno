#define F_CPU 8000000UL
#include<avr/io.h>   
#include<util/delay.h>

 #include "uart.h"

int main(void){
  unsigned char i; // temporary variable 

  init();

    PORTB = 0x00;   // turn ON all LEDs initially
  PORTA = 0XFF;
  while(1){
      // Read input from PORTA. 
    // This port will be connected to the 8 switches


    switch(PINA)
    { 
    case 0xFE:
      printf("Button 0\n") ;
    break;
    default:
      printf("nothing happening");
    }

    // Send output to PORTB. 
    // This port will be connected to the 8 LEDs
    i = PINA;
    PORTB = i;        
  }
  return 1; 
}

void init(void)
{
    DDRA  = 0x00;  // configure all 8 bits of PORTA as inputs
    DDRB  = 0xFF;  // configure all 8 bits of PORTD as outputs

    uart_init();
}
