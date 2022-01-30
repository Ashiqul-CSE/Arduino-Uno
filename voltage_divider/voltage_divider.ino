#define cellpin A5

const float mvpc = 4.55;
float counts = 0;
float mv = 0;
float multiplier = 3;
float output = 0;


void setup() {
  
Serial.begin(115200);
}

void loop() {
  
counts = analogRead (cellpin);

mv = counts * mvpc;

output = (mv * multiplier) / 1000;

Serial.print("output v:" + String (output));
delay(1000);
}
