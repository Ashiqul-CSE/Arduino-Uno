
//this project is made by Manish Kumar Yadav
int motorpin=9;
int motor= 7;
int sensorpin= A0;  
int sensorval;
int ledpin1=13;
int ledpin2=12;
int ledpin3=4;
int ledpin4=5;


void setup() {
  pinMode(motorpin,OUTPUT);
  pinMode(motor,OUTPUT);
  pinMode(sensorpin,INPUT); 
  pinMode(ledpin1,OUTPUT);
  pinMode(ledpin2,OUTPUT);
  pinMode(ledpin3,OUTPUT);
  pinMode(ledpin4,OUTPUT);
  
  //  setup code here, to run once:

}

void loop() {
  sensorval=analogRead(sensorpin);
  sensorval=sensorval/2.0741;
  
  if(sensorval>25)
  {
    digitalWrite(motorpin,HIGH);{
      
    
    digitalWrite(ledpin1,HIGH);
    digitalWrite(ledpin2,HIGH);
    }
    Serial.println("Fan ON");
    delay(500);
  }

  else if(sensorval>25)
  {
    digitalWrite(motorpin,LOW);{
      
    digitalWrite(ledpin1,LOW);
    digitalWrite(ledpin2,LOW);
    }
    Serial.println("Fan1 Fault");
    delay(500);
  }

  else if(sensorval>25)
  {
    digitalWrite(motor,LOW);{
      
    
    digitalWrite(ledpin3,LOW);
    digitalWrite(ledpin4,LOW);
    }
    Serial.println("Fan2 Fault");
    delay(500);
  }

  else if (sensorval>30)
  {
    digitalWrite(motorpin && motor,HIGH);{

      digitalWrite(ledpin1 && ledpin2 && ledpin3 && ledpin4,HIGH);
    }
    
   
    Serial.println("Dual Fan ON");
    delay(500);
    }

  else if (sensorval<=25)  

 {
    digitalWrite(motorpin && motor,LOW); {

       digitalWrite(ledpin1 && ledpin2 && ledpin3 &&  ledpin4,LOW);
    }
   
    Serial.println("Fan OFF");
    delay(500);
    }

   else if (sensorval>30)
  {


    digitalWrite(motorpin || motor, LOW); {
    
    digitalWrite(ledpin1 || ledpin2 || ledpin3 || ledpin4,LOW);
    
    }
    Serial.println("Fan Fault Alarm");
    delay(500);
    }
}
