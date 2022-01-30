
// initialize the variable

int tempval; // temparature variable
int fan1=9;
int fan2= 7;
int temp= A0;  // analog pin temp
int smoke = 6;  // smoke
int water = 8; // water
int door = 7;  // door
int LED = 11;  // door alarm + LED

// hall sensor pin

int hallsensor = 2;
int hallsensor1 = 3;
int hallsensor2 = 21; 
int hallsensor3 = 20;

int half_revolutions = 0;
int rpm = 0;
int half_revolutions2 = 0;
int rpm2 = 0;
int half_revolutions3 = 0;
int rpm3 = 0;
int half_revolutions4 = 0;
int rpm4 = 0;


unsigned long lastmillis = 0;

// this code will be executed every time the interrupt 0 (pin2) gets low.

void rpm_fan(){
 half_revolutions++;
}
void rpm_fan2(){
 half_revolutions2++;  
}

void rpm_fan3(){
 half_revolutions3++;
}
void rpm_fan4(){
 half_revolutions4++;  
}

void setup(){
 
Serial.begin(9600); 
pinMode(fan1, OUTPUT);
pinMode(fan2, OUTPUT);
pinMode(temp, INPUT);
pinMode(smoke, INPUT);
pinMode(water, INPUT);
pinMode(door, INPUT);
pinMode(LED, INPUT);

pinMode(hallsensor, INPUT);
pinMode(hallsensor1, INPUT);
pinMode(hallsensor2, INPUT);
pinMode(hallsensor3, INPUT);

//interrupt

attachInterrupt(0, rpm_fan, FALLING);
attachInterrupt(1, rpm_fan2, FALLING);
attachInterrupt(2, rpm_fan3, FALLING);
attachInterrupt(3, rpm_fan4, FALLING);

}
void loop(){
 
if (millis() - lastmillis == 1000){ //Uptade every one second, this will be equal to reading frecuency (Hz).

// data interrupt
 
detachInterrupt(0);//Disable interrupt when calculating
detachInterrupt(1);
detachInterrupt(2);
detachInterrupt(3);

rpm = half_revolutions * 30; // Convert frecuency to RPM, note: this works for one interruption per full rotation. For two interrups per full rotation use half_revolutions * 30.
rpm2 = half_revolutions2 * 30;
rpm3 = half_revolutions3 * 30;
rpm4  = half_revolutions4 * 30;

Serial.print("RPM =\t"); //print the word "RPM" and tab.
Serial.print(rpm); // print the rpm value.
Serial.print("\n");

Serial.print("RPM2 =\t"); //print the word "RPM" and tab.
Serial.println(rpm2); // print the rpm value.
Serial.print("\n");


Serial.print("RPM3 =\t"); //print the word "RPM" and tab.
Serial.print(rpm3); // print the rpm value.
Serial.print("\n");

Serial.print("RPM4 =\t"); //print the word "RPM" and tab.
Serial.println(rpm4); // print the rpm value.
Serial.print("\n");

half_revolutions = 0; // Restart the RPM counter
half_revolutions2 = 0;
half_revolutions3 = 0;
half_revolutions4 = 0;

lastmillis = millis(); // Uptade lasmillis

attachInterrupt(0, rpm_fan, FALLING); //enable interrupt
attachInterrupt(1, rpm_fan2, FALLING);
attachInterrupt(2, rpm_fan3, FALLING);
attachInterrupt(3, rpm_fan4, FALLING);

//smoke, water, door sensor logic
  
   if (smoke == HIGH)    {   
  digitalWrite(smoke, HIGH);
  Serial.println("Smoke Alarm"); {
     digitalWrite(fan1, LOW);
     digitalWrite(fan2, LOW);
    }
  delay(500);
  }

   if (water == HIGH)    {   
  digitalWrite(water, HIGH);
  Serial.println("Water Alarm");
  delay(500);
  }

   if (door == LOW)    {   
  digitalWrite(door, LOW); {
    digitalWrite(LED, HIGH);
    }
  Serial.println("Door Alarm");
  delay(500);
  }
  
//  Analog temparature value for fan fault problem

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
}
}
