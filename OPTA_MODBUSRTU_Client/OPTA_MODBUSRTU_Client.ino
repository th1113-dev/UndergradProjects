/**
  Getting Started with Modbus RTU on Opta™
  Name: Opta_Client
  Purpose: Writes Coil and Holding Register values; Reads Coil, Discrete Input, Holding Registers, and Input Register values.

  @author Arduino
  student: Theodis Hill (UID:118983264)
*/

#include <ArduinoModbus.h>
#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library

constexpr auto baudrate { 19200 };

// Calculate preDelay and postDelay in microseconds as per Modbus RTU Specification
// MODBUS over serial line specification and implementation guide V1.02
// Paragraph 2.5.1.1 MODBUS Message RTU Framing
// https://modbus.org/docs/Modbus_over_serial_line_V1_02.pdf
constexpr auto bitduration { 1.f / baudrate };
constexpr auto preDelayBR { bitduration * 9.6f * 3.5f * 1e6 };
constexpr auto postDelayBR { bitduration * 9.6f * 3.5f * 1e6 };
// constexpr auto preDelayBR { bitduration * 10.0f * 3.5f * 1e6 };

int counter = 0;

void setup() {
    Serial.begin(9600);
    while (!Serial);

    Serial.println("Modbus RTU Client");

    RS485.setDelays(preDelayBR, postDelayBR);

    // Start the Modbus RTU client
    if (!ModbusRTUClient.begin(baudrate, SERIAL_8E1)) {
        Serial.println("Failed to start Modbus RTU Client!");
        while (1);
    }
}

void loop() {
    writeCoilValues();

    readCoilValues();

    readDiscreteInputValues();

    writeHoldingRegisterValues();

    readHoldingRegisterValues();

    readInputRegisterValues();

    counter++;

    delay(5000);
    Serial.println();
}

/**
  Writes Coil values to the server under specified address.
*/
void writeCoilValues() {
    // Set the coils to 1 when counter is odd
    byte coilValue = ((counter % 2) == 0) ? 0x00 : 0x01;

    Serial.print("Writing Coil values ... ");

    // Srite 10 Coil values to (server) id 42, address 0x00
    ModbusRTUClient.beginTransmission(42, COILS, 0x00, 10);
    for (int i = 0; i < 10; i++) {
        ModbusRTUClient.write(coilValue);
    }
    if (!ModbusRTUClient.endTransmission()) {
        Serial.print("failed! ");
        Serial.println(ModbusRTUClient.lastError());
    } else {
        Serial.println("success");
    }

    // Alternatively, to write a single Coil value use:
    // ModbusRTUClient.coilWrite(...)
}

/**
  Reads Coil values from the server under specified address.
*/
void readCoilValues() {
    Serial.print("Reading Coil values ... ");

    // Read 10 Coil values from (server) id 42, address 0x00
    if (!ModbusRTUClient.requestFrom(42, COILS, 0x00, 10)) {
        Serial.print("failed! ");
        Serial.println(ModbusRTUClient.lastError());
    } else {
        Serial.println("success");

        while (ModbusRTUClient.available()) {
            Serial.print(ModbusRTUClient.read());
            Serial.print(' ');
        }
        Serial.println();
    }

    // Alternatively, to read a single Coil value use:
    // ModbusRTUClient.coilRead(...)
}

/**
  Reads Discrete Input values from the server under specified address.
*/
void readDiscreteInputValues() {
    Serial.print("Reading Discrete Input values ... ");

    // Read 10 Discrete Input values from (server) id 42, address 0x00
    if (!ModbusRTUClient.requestFrom(42, DISCRETE_INPUTS, 0x00, 10)) {
        Serial.print("failed! ");
        Serial.println(ModbusRTUClient.lastError());
    } else {
        Serial.println("success");

        while (ModbusRTUClient.available()) {
            Serial.print(ModbusRTUClient.read());
            Serial.print(' ');
        }
        Serial.println();
    }

    // Alternatively, to read a single Discrete Input value use:
    // ModbusRTUClient.discreteInputRead(...)
}

/**
  Writes Holding Register values to the server under specified address.
*/
void writeHoldingRegisterValues() {
    //Set the Holding Register values to counter
    Serial.print("Writing Holding Registers values ... ");

    // Write 10 coil values to (server) id 42, address 0x00
    ModbusRTUClient.beginTransmission(42, HOLDING_REGISTERS, 0x00, 10);
    for (int i = 0; i < 10; i++) {
        ModbusRTUClient.write(counter);
    }
    if (!ModbusRTUClient.endTransmission()) {
        Serial.print("failed! ");
        Serial.println(ModbusRTUClient.lastError());
    } else {
        Serial.println("success");
    }

    // Alternatively, to write a single Holding Register value use:
    // ModbusRTUClient.holdingRegisterWrite(...)
}

/**
  Reads Holding Register values from the server under specified address.
*/
void readHoldingRegisterValues() {
    Serial.print("Reading Holding Register values ... ");

    // Read 10 Input Register values from (server) id 42, address 0x00
    if (!ModbusRTUClient.requestFrom(42, HOLDING_REGISTERS, 0x00, 10)) {
        Serial.print("failed! ");
        Serial.println(ModbusRTUClient.lastError());
    } else {
        Serial.println("success");

        while (ModbusRTUClient.available()) {
            Serial.print(ModbusRTUClient.read());
            Serial.print(' ');
        }
        Serial.println();
    }

    // Alternatively, to read a single Holding Register value use:
    // ModbusRTUClient.holdingRegisterRead(...)
}

/**
  Reads Input Register values from the server under specified address.
*/
void readInputRegisterValues() {
    Serial.print("Reading input register values ... ");

    // Read 10 discrete input values from (server) id 42,
    if (!ModbusRTUClient.requestFrom(42, INPUT_REGISTERS, 0x00, 10)) {
        Serial.print("failed! ");
        Serial.println(ModbusRTUClient.lastError());
    } else {
        Serial.println("success");

        while (ModbusRTUClient.available()) {
            Serial.print(ModbusRTUClient.read());
            Serial.print(' ');
        }
        Serial.println();
    }

    // Alternatively, to read a single Input Register value use:
    // ModbusRTUClient.inputRegisterRead(...)
}