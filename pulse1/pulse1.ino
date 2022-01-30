                                                 
byte PWM_PIN = 2;
byte PWM_PIN1 = 3;
byte PWM_PIN2 = 5;
byte PWM_PIN3 = 6;
 
int pwm_value;
int pwm_value2;
int pwm_value3;
int pwm_value4;
 
void setup() {
  pinMode(PWM_PIN, INPUT);
  pinMode(PWM_PIN1, INPUT);
  pinMode(PWM_PIN2, INPUT);
  pinMode(PWM_PIN3, INPUT);
  Serial.begin(115200);
  delay (500)
}
 
void loop() {
  pwm_value = pulseIn(PWM_PIN, HIGH);
  pwm_value1 = pulseIn(PWM_PIN1, HIGH);
  pwm_value2 = pulseIn(PWM_PIN2, HIGH);
  pwm_value3 = pulseIn(PWM_PIN3, HIGH);
  Serial.println(pwm_value);
  Serial.println(pwm_value2);
  Serial.println(pwm_value3);
  Serial.println(pwm_value4);
}
