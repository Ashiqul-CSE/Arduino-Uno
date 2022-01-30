void setup() 
{ 
  Serial.begin(9600);
} 
 
void loop() 
{ 
  int data= analogRead(0); 
  byte angle= map(data, 0, 1023, 0, 180);   
  Serial.write(angle); 
  delay(50);                           
} 
