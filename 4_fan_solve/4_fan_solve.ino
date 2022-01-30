#include <Arduino.h>
#include "FanMonitor.h"

// *
// * Pins
// *
#define FAN_MONITOR_PIN 5

#define FAN_MONITOR_PIN1 6

#define FAN_MONITOR_PIN2 9

#define FAN_MONITOR_PIN3 10

// *
// * Define the FanMonitor instance to monitor
// * the 3-wire fan.
// *
FanMonitor _fanMonitor = FanMonitor(FAN_MONITOR_PIN, FAN_TYPE_BIPOLE);
FanMonitor _fanMonitor1 = FanMonitor(FAN_MONITOR_PIN1, FAN_TYPE_BIPOLE);
FanMonitor _fanMonitor2 = FanMonitor(FAN_MONITOR_PIN2, FAN_TYPE_BIPOLE);
FanMonitor _fanMonitor3 = FanMonitor(FAN_MONITOR_PIN3, FAN_TYPE_BIPOLE);

void setup()
{
  // *
  // * Initialize the serial port.
  // *
  Serial.begin(115200);

  // *
  // * Initialize the fan monitor.
  // *
  _fanMonitor.begin();
  _fanMonitor1.begin();
  _fanMonitor2.begin();
  _fanMonitor3.begin();
}

void loop()
{
  // *
  // * Get the fan speed.
  // *
  uint16_t rpm = _fanMonitor.getSpeed();
  uint16_t rpm1 = _fanMonitor1 .getSpeed();
  uint16_t rpm2 = _fanMonitor2 .getSpeed();
  uint16_t rpm3 = _fanMonitor3 .getSpeed();

  // *
  // * Print the speed to the serial port.
  // *
  Serial.print("Fan 1 = "); Serial.print(rpm); Serial.println(" RPM");
  Serial.print("Fan 2 = "); Serial.print(rpm1); Serial.println(" RPM");
  Serial.print("Fan 3 = "); Serial.print(rpm2); Serial.println(" RPM");
  Serial.print("Fan 4 = "); Serial.print(rpm3); Serial.println(" RPM");
  
  // *
  // * Delay 1 second.
  // *
  delay(1000);
}
