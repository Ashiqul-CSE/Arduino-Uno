char dat[10];                          // buffer for receving/sending messages
char i,j;

sbit  rs485_rxtx_pin  at RC2_bit;               // set transcieve pin
sbit  rs485_rxtx_pin_direction at TRISC2_bit;   // set transcieve pin direction

// Interrupt routine
void interrupt() {
  RS485Master_Receive(dat);
}

void main(){
  long cnt = 0;

  ANSEL  = 0;                          // Configure AN pins as digital I/O
  ANSELH = 0;
  C1ON_bit = 0;                        // Disable comparators
  C2ON_bit = 0;
  
  PORTB  = 0;
  PORTD  = 0;
  TRISB  = 0;
  TRISD  = 0;


  UART1_Init(9600);                    // initialize UART1 module
  Delay_ms(100);

  RS485Master_Init();                  // initialize MCU as Master
  dat[0] = 0xAA;
  dat[1] = 0xF0;
  dat[2] = 0x0F;
  dat[4] = 0;                          // ensure that message received flag is 0
  dat[5] = 0;                          // ensure that error flag is 0
  dat[6] = 0;

  RS485Master_Send(dat,1,160);


  RCIE_bit = 1;                        // enable interrupt on UART1 receive
  TXIE_bit = 0;                        // disable interrupt on UART1 transmit
  PEIE_bit = 1;                        // enable peripheral interrupts
  GIE_bit = 1;                         // enable all interrupts

  while (1){
                                       // upon completed valid message receiving
                                       //   data[4] is set to 255
    cnt++;
    if (dat[5])  {                     // if an error detected, signal it
      PORTD = 0xAA;                    //   by setting portd to 0xAA
    }
    if (dat[4]) {                      // if message received successfully
      cnt = 0;
      dat[4] = 0;                      // clear message received flag
      j = dat[3];
      for (i = 1; i <= dat[3]; i++) {  // show data on PORTB
        PORTB = dat[i-1];
      }                                // increment received dat[0]
      dat[0] = dat[0]+1;               // send back to master
      Delay_ms(1);
      RS485Master_Send(dat,1,160);

    }
   if (cnt > 100000) {
      PORTD ++;
      cnt = 0;
      RS485Master_Send(dat,1,160);
      if (PORTD > 10)                  // if sending failed 10 times
        RS485Master_Send(dat,1,50);    //   send message on broadcast address
     }
  }

}
