int readpin=A5;
float V2=0;
int delayTime=1000;
int readval;


void setup() {
  // put your setup code here, to run once:
pinMode(readpin,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
readval=analogRead(readpin);
V2=(5./1023.)*readval;
Serial.println(V2);
delay(delayTime);
}
