
int motorPin = 3;       // the pin that the motor is attached to
int pot = A4;     // potentiometer is connected to analog pin 0

void setup()  {
  // declare pin 3 and A0 to be an output and input respectively:
  pinMode(motorPin, OUTPUT);
  pinMode(pot, INPUT);
  Serial.begin(9600);          //  setup serial
}

int getPotValue() {
  int potAnValue = analogRead(pot);    // read the input pin
  int potPWMValue = map(potAnValue, 0, 1023, 0, 255); // mapping to get 0 to 255
  if (potPWMValue < 50)
    potPWMValue = 0;
  else
    potPWMValue = min(potPWMValue, 255);
  // below PWM value 50 use 0 to avoid rough run
  return potPWMValue;               
}

// the loop routine runs over and over again forever:
void loop()  {
  // set the PWM value on pin 3 for motor speed control
  analogWrite(motorPin, getPotValue());
  // print out getPotValue to serial monitor
  Serial.println(getPotValue());
  // 20 ms delay (can add noticible delay if over 200ms)
  delay(20);
}
