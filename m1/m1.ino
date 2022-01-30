unsigned long lastmillis = 0;

volatile int rpmcounter1 = 0;
volatile int rpmcounter2 = 0;
volatile int rpmcounter3 = 0;
volatile int rpmcounter4 = 0;

int rpm1 = 0;
int rpm2 = 0;
int rpm3 = 0;
int rpm4 = 0;


void hallSensor1() {
  rpmcounter1++;
}

void hallSensor2() {
  rpmcounter2++;
}

void hallSensor3() {
  rpmcounter3++;
}

void hallSensor4() {
  rpmcounter4++;
}



void setup() {

  Serial.begin(115200);

  attachInterrupt(0, hallSensor1, FALLING);//interrupt 0 is on pin 2
  attachInterrupt(1, hallSensor2, FALLING);//interrupt 1 is on pin 3
  attachInterrupt(2, hallSensor3, FALLING);//interrupt 2 is on pin 21
  attachInterrupt(3, hallSensor4, FALLING);//interrupt 3 is on pin 20

}

void loop() {

  if (millis() - lastmillis == 1000) {
    noInterrupts();
    rpm1 = rpmcounter1 * 30;
    rpm2 = rpmcounter2 * 30;
    rpm3 = rpmcounter3 * 30;
    rpm4 = rpmcounter4 * 30;
    
    interrupts();

    rpmcounter1 = rpmcounter2 = rpmcounter3 =  rpmcounter4 = 0;

    lastmillis = millis();

    Serial.print("fan1: ");
    Serial.print(rpm1);
    Serial.print("\t");
    Serial.print("fan2: ");
    Serial.print(rpm2);
    Serial.print("\t");
    Serial.print("fan3: ");
    Serial.print(rpm3);
    Serial.print("\t");
    Serial.print("fan4: ");
    Serial.print(rpm4);
    Serial.print("\t");
    Serial.print("\n");
    delay(1000);
  }

}
