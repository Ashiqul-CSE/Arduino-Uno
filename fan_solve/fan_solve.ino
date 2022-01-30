int rotate;
int Calc;
int tempval;
 

//The pin location of the sensor
int hallsensor = 2;
int hallsensor1 = 3;
int hallsensor2 = 4;
int hallsensor3 = 5;
int fan1=9;
int fan2= 7;
int temp= A0; 

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

{ rotate++; }
 
//This is the setup function where the serial port is initialised,
//and the interrupt is attached

void setup()

{ 
  pinMode(fan1, OUTPUT);
  pinMode(fan2, OUTPUT);
  pinMode(temp, INPUT);
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

  tempval=analogRead(temp);
  tempval=tempval/2.0741;


 if(tempval>25)
  {
    digitalWrite(fan1,HIGH);{
      
    
    digitalWrite(hallsensor,HIGH);
    digitalWrite(hallsensor1,HIGH);
    }
    Serial.println("Fan ON");
    delay(500);
  }

  else if(tempval>25)
  {
    digitalWrite(fan1,LOW);{
      
    digitalWrite(hallsensor,LOW);
    digitalWrite(hallsensor1,LOW);
    }
    Serial.println("Fan1 Fault");
    delay(500);
  }

  else if(tempval>25)
  {
    digitalWrite(fan2,LOW);{
      
    
    digitalWrite(hallsensor2,LOW);
    digitalWrite(hallsensor3,LOW);
    }
    Serial.println("Fan2 Fault");
    delay(500);
  }

  else if (tempval>30)
  {
    digitalWrite(fan1 && fan2,HIGH);{

      digitalWrite(hallsensor && hallsensor1 && hallsensor2 && hallsensor3,HIGH);
    }
    
   
    Serial.println("Dual Fan ON");
    delay(500);
    }

  else if (tempval<=25)  

 {
    digitalWrite(fan1 && fan2,LOW); {

       digitalWrite(hallsensor && hallsensor1 && hallsensor2 &&  hallsensor3,LOW);
    }
   
    Serial.println("Fan OFF");
    delay(500);
    }

   else if (tempval>30)
  {


    digitalWrite(fan1 || fan2, LOW); {
    
    digitalWrite(hallsensor || hallsensor1 || hallsensor2 || hallsensor3,LOW);
    
    }
    Serial.println("Fan Fault Alarm");
    delay(500);
    }

  
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
} 
