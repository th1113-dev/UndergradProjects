/**
  Name: MODBUS RTU Switch and temp. reader - Server/Worker
  Purpose: Reports the values of switches and relays to the Master/Client OPTA.

  @author Theodis Hill (UID:118983264)
*/

#include <ArduinoRS485.h> 
#include <ArduinoModbus.h>

constexpr auto baudrate { 19200 };

constexpr auto bitduration { 1.f / baudrate };
constexpr auto preDelayBR { bitduration * 9.6f * 3.5f * 1e6 };
constexpr auto postDelayBR { bitduration * 9.6f * 3.5f * 1e6 };

const int numCoils = 2;
const int numDiscreteInputs = 8;
const int numHoldingRegisters = 10;
const int numInputRegisters = 10;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Connected to client. Ready to serve!");

  RS485.setDelays(preDelayBR, postDelayBR);

  // Start the Modbus RTU client
  if (!ModbusRTUServer.begin(42, baudrate, SERIAL_8E1)) {
      Serial.println("Failed to start Modbus RTU Client!");
      while (1);
  }

  // Configure coils at address 0x00
  ModbusRTUServer.configureCoils(0x00, numCoils);

  // Configure discrete inputs at address 0x00
  ModbusRTUServer.configureDiscreteInputs(0x00, numDiscreteInputs);

  // Configure holding registers at address 0x00
  ModbusRTUServer.configureHoldingRegisters(0x00, numHoldingRegisters);

  // Configure input registers at address 0x00
  ModbusRTUServer.configureInputRegisters(0x00, numInputRegisters);
}

void loop() {


  // Poll for Modbus RTU requests
  ModbusRTUServer.poll();
    
    //Hopefully defining the relays (Changed from test video. as long as the relays are open, these will b
      
//Defining the inputs from the switches 
  ModbusRTUServer.discreteInputWrite(0, digitalRead(A0));
  ModbusRTUServer.discreteInputWrite(1, digitalRead(A1));
  ModbusRTUServer.discreteInputWrite(2, digitalRead(A2));
  ModbusRTUServer.discreteInputWrite(3, digitalRead(A3));
  ModbusRTUServer.discreteInputWrite(4, digitalRead(A4));
  ModbusRTUServer.discreteInputWrite(5, digitalRead(A5));
  ModbusRTUServer.discreteInputWrite(6, digitalRead(A6));
  ModbusRTUServer.discreteInputWrite(7, digitalRead(A7));

}

