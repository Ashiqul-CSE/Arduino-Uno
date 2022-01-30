 #include <SPI.h>
    #include <Wire.h>
   #include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27, 16, 2);
    int tON=0;
    int tOFF=0;
    int Tperiod=0;
    int freq=0;
    int RPM=0;
    void setup() 
    {
      
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
    display.display();
    delay(1000);
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.setTextColor(WHITE);
    pinMode(3,OUTPUT);
    }
    
    void loop() 
    {
    tON=pulseIn(3,HIGH);
    tOFF=pulseIn(3,LOW);
    Tperiod=tON + tOFF;
    freq= 1000000.0/ Tperiod;
    RPM=freq * 15;
    if(digitalRead(3)==HIGH)
    {
//    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("RPM  METER ");
    display.setCursor(0, 10);
    display.print("Frequency: ");
    display.print(freq);
    display.println(" Hz");
    display.setCursor(0, 20);
    display.print("RPM: ");
    display.print(RPM);
    display.display();
    delay(1000);
    display.clearDisplay();
    }
    tON=0;
    tOFF=0;
    Tperiod=0;
    freq=0;
    RPM=0;
    }
                 
