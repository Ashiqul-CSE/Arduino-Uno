int NbTopsFan; int Calc;
 
//The pin location of the sensor
int hallsensor = 2;
int hallsensor1 = 3;
int hallsensor2 = 4;
int hallsensor3 = 5;

typedef struct{
 
//Defines the structure for multiple fans and 
//their dividers 
char fantype;
unsigned int fandiv; 
}
fanspec;
 

//This is the varible used to select the fan and it's divider,
//set 1 for unipole hall effect sensor
//and 2 for bipole hall effect sensor

fanspec fanspace[3]={{0,1},{1,2},{2,8}}; char fan = 1;
 
void rpm ()
//This is the function that the interupt fan fault alarm

{ NbTopsFan++; }
 
//This is the setup function where the serial port is initialised,
//and the interrupt is attached

void setup()

{ 
  pinMode(hallsensor, OUTPUT);
  pinMode(hallsensor1, OUTPUT);
  pinMode(hallsensor2, OUTPUT);
  pinMode(hallsensor3, OUTPUT);

Serial.begin(9600);
attachInterrupt(0, rpm, RISING);
}
 
void loop ()
//Set NbTops to 0 ready for calculations
{
  
  NbTopsFan = 0;
 
//Enables interrupts
sei();
 
//Wait 5 second
delay (5000);
 
//Disable interrupts
cli();
 
//Times NbTopsFan (which is apprioxiamately the fequency the fan 
//is spinning at) by 60 seconds before dividing by the fan's divider
Calc = ((NbTopsFan * 60)/fanspace[fan].fandiv);
 
//Prints the number calculated above
Serial.print (Calc, DEC);
 
//Prints " rpm" and a new line
Serial.print (" rpm\r\n");
} 
