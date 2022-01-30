char dat[9];             // buffer for receving/sending messages
char i,j;

sbit  rs485_rxtx_pin at RC2_bit;             // set transcieve pin
sbit  rs485_rxtx_pin_direction at TRISC2_bit;   // set transcieve pin direction

// Interrupt routine
void interrupt() {
 RS485Slave_Receive(dat);
}

void main() {
  ANSEL  = 0;                        // Configure AN pins as digital I/O
  ANSELH = 0;
  C1ON_bit = 0;                      // Disable comparators
  C2ON_bit = 0;
  
  PORTB = 0;
  PORTD = 0;
  TRISB = 0;
  TRISD = 0;


  UART1_Init(9600);                  // initialize UART1 module
  Delay_ms(100);
  RS485Slave_Init(160);              // Intialize MCU as slave, address 160

  dat[4] = 0;                        // ensure that message received flag is 0
  dat[5] = 0;                        // ensure that message received flag is 0
  dat[6] = 0;                        // ensure that error flag is 0

  RCIE_bit = 1;                      // enable interrupt on UART1 receive
  TXIE_bit = 0;                      // disable interrupt on UART1 transmit
  PEIE_bit = 1;                      // enable peripheral interrupts
  GIE_bit = 1;                       // enable all interrupts

  while (1) {
    if (dat[5])  {                   // if an error detected, signal it by
      PORTD = 0xAA;                  //   setting portd to 0xAA
      dat[5] = 0;
    }
    if (dat[4]) {                    // upon completed valid message receive
      dat[4] = 0;                    //   data[4] is set to 0xFF
      j = dat[3];
      for (i = 1; i <= dat[3];i++){
        PORTB = dat[i-1];
      }
      dat[0] = dat[0]+1;             // increment received dat[0]
      Delay_ms(1);
      RS485Slave_Send(dat,1);        //   and send it back to master
    }
  }
}
