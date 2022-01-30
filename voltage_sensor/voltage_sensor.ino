

int offset =20;// set the correction offset value
void setup() {
  
  Serial.begin(9600);
}

void loop() {
  
  int volt = analogRead(A0);// read the input
  double voltage = map(volt,0,1023, 0, 2500) + offset;// map 0-1023 to 0-2500 and add correction offset
  
  voltage /=100;// divide by 100 to get the decimal values
  Serial.print("Voltage: ");
  Serial.print(voltage);//print the voltge
  Serial.println("V");

delay(500);
  
  
}
