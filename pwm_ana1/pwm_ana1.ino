
int pwmPin9 = 9;
int pwmPin10 = 10;
int pwmPin3 = 3;
int pwmPin11 = 11;

void setup()
{
    TCCR1B = TCCR1B & B11111000 | B00000001; // Set PWM frequency for D9 & D10:
    pinMode(pwmPin9, OUTPUT); // Sets the pin as output
    pinMode(pwmPin10, OUTPUT); // Sets the pin as output


    TCCR2B = TCCR2B & B11111000 | B00000001; // Set PWM for D3 & D11
    pinMode(pwmPin3, OUTPUT); // Sets the pin as output
    pinMode(pwmPin11, OUTPUT); // Sets the pin as output
}

void loop() {
  // put your main code here, to run repeatedly:

}
