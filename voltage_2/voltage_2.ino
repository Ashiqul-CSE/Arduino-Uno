const float vpp = 0.0044;
float current; 

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

current = analogRead(A5); // 1023
current *= vpp; // Back into voltage
current /=4.7; // voltage drop divided by ohms = current
Serial.println(current, 4);
delay(1000);
}
