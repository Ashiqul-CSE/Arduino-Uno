int half_revolutions = 0;
int rpm = 0;
int half_revolutions2 = 0;
int rpm2 = 0;

unsigned long lastmillis = 0;

void setup(){
 
Serial.begin(9600); 
attachInterrupt(0, rpm_fan, FALLING);
attachInterrupt(1, rpm_fan2, FALLING);

}
void loop(){
 
if (millis() - lastmillis == 1000){ //Uptade every one second, this will be equal to reading frecuency (Hz).
 
detachInterrupt(0);//Disable interrupt when calculating
detachInterrupt(1);

rpm = half_revolutions * 30; // Convert frecuency to RPM, note: this works for one interruption per full rotation. For two interrups per full rotation use half_revolutions * 30.
rpm2 = half_revolutions2 * 30;


Serial.print("RPM =\t"); //print the word "RPM" and tab.
Serial.print(rpm); // print the rpm value.
Serial.print("\n");

Serial.print("RPM2 =\t"); //print the word "RPM" and tab.
Serial.println(rpm2); // print the rpm value.
Serial.print("\n");

half_revolutions = 0; // Restart the RPM counter
half_revolutions2 = 0;

lastmillis = millis(); // Uptade lasmillis

attachInterrupt(0, rpm_fan, FALLING); //enable interrupt
attachInterrupt(1, rpm_fan2, FALLING);

     
 }
}
// this code will be executed every time the interrupt 0 (pin2) gets low.

void rpm_fan(){
 half_revolutions++;
}
void rpm_fan2(){
 half_revolutions2++;  
}
