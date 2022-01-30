#include <ModbusRTUMaster.h>
#include <RS485.h>
const uint8_t slaveAddress = 1;
const uint32_t serialRate = 38400UL;
const int serialConfig = SERIAL_8N1;
const uint32_t requestPeriod = 1000UL; // ms
const int numInputs = 5;
ModbusRTUMaster modbus(RS485);
uint8_t inputStates[numInputs];
uint16_t inputCounters[numInputs];
////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600L);
  Serial.println("seneca-z-d-in-module started");
  RS485.begin(serialRate, HALFDUPLEX, serialConfig);
  modbus.begin(serialRate);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  static uint32_t lastRequestTime = millis();
  // Send a request every 1000ms
  if (!modbus.isWaitingResponse()) {
    if (millis() - lastRequestTime > requestPeriod) {
      // Send a Read Holding Registers request to the slave with address 1
      // IMPORTANT: all read and write functions start a Modbus transmission, but they are not
      // blocking, so you can continue the program while the Modbus functions work. To check for
      // available responses, call modbus.available() function often.
      if (!modbus.readHoldingRegisters(slaveAddress, 1, 6)) {
        // TODO Failure treatment
      }
      lastRequestTime = millis();
    }
  }
  // Check available responses often
  ModbusResponse response = modbus.available();
  if (response) {
    if (response.hasError()) {
      // TODO Response failure treatment. You can use response.getErrorCode()
      // to get the error code.
    } else {
      uint16_t states = response.getRegister(0);
      for (int i = 0; i < numInputs; ++i) {
        inputStates[i] = (states >> i) & 0x01;
        inputCounters[i] = response.getRegister(i + 1);
      }
      printInputs();
    }
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void printInputs() {
  Serial.println();
  Serial.print("Inputs: ");
  for (int i = 0; i < numInputs; ++i) {
    Serial.print(inputStates[i] ? "HIGH" : "LOW ");
    Serial.print(' ');
  }
  Serial.println();
  Serial.print("Counters: ");
  for (int i = 0; i < numInputs; ++i) {
    Serial.print(inputCounters[i]);
    Serial.print(' ');
  }
  Serial.println();
}
