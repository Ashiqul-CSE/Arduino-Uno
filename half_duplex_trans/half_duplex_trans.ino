const int ledPin =  13;  // Built-in LED
const int EnTxPin =  2;  // HIGH:Transmitter, LOW:Receiver
void setup() 
{ 
  Serial.begin(9600);
  Serial.setTimeout(100);  
  pinMode(ledPin, OUTPUT);
  pinMode(EnTxPin, OUTPUT);
  digitalWrite(ledPin, LOW); 
  digitalWrite(EnTxPin, HIGH); 
} 
 
void loop() 
{   
  int rdata = analogRead(0); //data from potentiometer 
  int angle= map(rdata, 0, 1023, 0, 180); 
  
  //transmitter data packet
  Serial.print("I"); //initiate data packet
  Serial.print("S"); //code for servo
  Serial.print(angle); //servo angle data
  Serial.print("F"); //finish data packet
  delay(50); 

  //receiver data packet
  Serial.print("I"); //initiate data packet
  Serial.print("L"); //code for sensor
  Serial.print("F"); //finish data packet
  Serial.flush();    
  
  digitalWrite(EnTxPin, LOW); //RS485 as receiver

  if(Serial.find("i"))
  {
      int data=Serial.parseInt(); 
      if(Serial.read()=='f') //finish reading
       {
         onLED(data);            
      }
      
  }
  digitalWrite(EnTxPin, HIGH); //RS485 as transmitter
  
} 

void onLED(int data)
{
  if(data>500)
     digitalWrite(ledPin, HIGH); 
  else
     digitalWrite(ledPin, LOW); 
}
