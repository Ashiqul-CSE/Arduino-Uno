int rotate; 
int Calc;
int Calc1;
int Calc2;
int Calc3;
 
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



 typedef struct{
 
//Defines the structure for multiple fans and 
//their dividers 
char fantype1;
unsigned int fandiv1; 
}
fanspec1;


typedef struct{
 
//Defines the structure for multiple fans and 
//their dividers 
char fantype2;
unsigned int fandiv2; 
}
fanspec2;



typedef struct{
 
//Defines the structure for multiple fans and 
//their dividers 
char fantype3;
unsigned int fandiv3; 
}
fanspec3;


//This is the varible used to select the fan and it's divider,
//set 1 for unipole hall effect sensor
//and 2 for bipole hall effect sensor

fanspec fanspace[3]={{0,1},{1,2},{2,8}}; char fan = 1;

fanspec1 fanspace1[3]={{0,1},{1,2},{2,8}}; char fan1 = 1;

fanspec2 fanspace2[3]={{0,1},{1,2},{2,8}}; char fan2 = 1;

fanspec3 fanspace3[3]={{0,1},{1,2},{2,8}}; char fan3 = 1;

 
void rpm ()
//This is the function that the interupt calls

{ rotate++; }


 void rpm1 ()
//This is the function that the interupt calls

{ rotate++; }


void rpm2 ()
//This is the function that the interupt calls

{ rotate++; }

void rpm3 ()
//This is the function that the interupt calls

{ rotate++; }
//This is the setup function where the serial port is initialised,
//and the interrupt is attached

void setup()

{ 
  pinMode(hallsensor, INPUT);
   pinMode(hallsensor1, INPUT);
    pinMode(hallsensor, INPUT);
     pinMode(hallsensor3, INPUT);
  
Serial.begin(9600);
attachInterrupt(0, rpm, RISING);
attachInterrupt(1, rpm1, RISING);
attachInterrupt(2, rpm2, RISING);
attachInterrupt(3, rpm3, RISING);
delay(500);
}
 
void loop ()
//Set NbTops to 0 ready for calculations
{
  
  rotate = 0;
 
//Enables interrupts
sei();
 
//Wait 1 second
delay (1000);
 
//Disable interrupts
cli();
 
//Times NbTopsFan (which is apprioxiamately the fequency the fan 
//is spinning at) by 60 seconds before dividing by the fan's divider
Calc = ((rotate * 60)/fanspace[fan].fandiv);
 
//Prints the number calculated above
Serial.print (Calc, DEC);
 
//Prints " rpm" and a new line
Serial.print (" rpm\r\n");

Calc1 = ((rotate * 60)/fanspace1[fan1].fandiv1);
 
//Prints the number calculated above
Serial.print (Calc1, DEC);

Serial.print (" rpm1\r\n");

Calc2 = ((rotate * 60)/fanspace2[fan2].fandiv2);
 
//Prints the number calculated above
Serial.print (Calc2, DEC);

Serial.print (" rpm2\r\n");

Calc = ((rotate * 60)/fanspace3[fan3].fandiv3);
 
//Prints the number calculated above
Serial.print (Calc3, DEC);

Serial.print (" rpm3\r\n");
} 
