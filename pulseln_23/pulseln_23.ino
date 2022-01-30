int pin = A0;
int pin1 = A1;
int pin2 = A2;
int pin3 = A3;



unsigned long duration;
unsigned long duration1;
unsigned long duration2;
unsigned long duration3;

unsigned int rpm;
unsigned int rpm1;
unsigned int rpm2;
unsigned int rpm3;

void setup()
{
  pinMode(pin, INPUT);
   pinMode(pin1, INPUT);
    pinMode(pin2, INPUT);
     pinMode(pin3, INPUT);
     
  Serial.begin(9600);
}

void loop()
{
  duration = pulseIn(pin, HIGH);
  rpm = ((2200L*6550)/duration);
  Serial.println(rpm);
  delay(1000)

    duration1 = pulseIn(pin1, HIGH);
  rpm1 = ((2200L*6550)/duration1);
  Serial.println(rpm1);
  delay(1000)

    duration2 = pulseIn(pin2, HIGH);
  rpm2 = ((2200L*6550)/duration2);
  Serial.println(rpm2);
  delay(1000)


    duration3 = pulseIn(pin3, HIGH);
  rpm3 = ((2200L*6550)/duration3);
  Serial.println(rpm3);
  delay(1000)

}
