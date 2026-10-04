/**
  Name: MODBUS RTU Switch and temp. reader - Client/Master
  Purpose: Prints the outputs given by the Worker/Server OPTA in set amounts of time.
  Those outputs being the conditions of the switches (1-8), the temperature of the room
  And the conditions of the relays. 

  @author Theodis Hill (UID:118983264)
*/

#include <ArduinoModbus.h>
#include <ArduinoRS485.h> 

constexpr auto baudrate { 19200 };

constexpr auto bitduration { 1.f / baudrate };
constexpr auto preDelayBR { bitduration * 9.6f * 3.5f * 1e6 };
constexpr auto postDelayBR { bitduration * 9.6f * 3.5f * 1e6 };

float temp = 0.0;
bool switches[8]; 
bool relays[2];



void setup() {
     pinMode(D0, OUTPUT);
      pinMode(D1, OUTPUT);
    Serial.begin(9600);
    while (!Serial);

    Serial.println("Connected to worker. Ready to rock.");

    RS485.setDelays(preDelayBR, postDelayBR);

    // Start the Modbus RTU client
    if (!ModbusRTUClient.begin(baudrate, SERIAL_8E1)) {
        Serial.println("Failed to start Modbus RTU Client!");
        while (1);
    }

}

void loop() {

    //Want to make an interrupt here maybe
unsigned long seconds = millis()/1000;
    //Temperature function:
     int sensorValueA0 = analogRead(A0);
   float voltageA0 = sensorValueA0 * (3.0 / 4095.0)/ 0.3;
  temp = (voltageA0 -0.500)/.010;
    Switchreader();
digitalWrite(D0, switches[0] );
digitalWrite(D1, switches[1] );

    // output/deliverables (Sorry I had fun with the borders lol):
    Serial.println("User note! 'X' means it's on ' ' means it's off... or my creator messed up.");
    Serial.println();
    Serial.println();
    Serial.println("I wake.");
    Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |O c O| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    Serial.println();
    Serial.print("Time: "); Serial.print(seconds); Serial.println(" - Seconds");
    
    Serial.println("|| Realay 1 || Relay 2 || Temp. || S1 || S2 || S3 || S4 || S5 || S6 || S7 || S8 ||");
    Serial.print("|| ");
   
        if (digitalRead(D0))
        Serial.print("   X   ");
        else 
        Serial.print("       ");

Serial.print(" || ");

      if (digitalRead(D1))
        Serial.print("   X   ");
        else 
        Serial.print("       ");
    
        Serial.print(" || ");

   
    Serial.print(temp);
    Serial.print(" || ");

    for (int n = 0; n < 8 ; n++){
        Serial.print(switches[n] ? "X " : "  ");
        Serial.print(" || ");
    }
    Serial.println();
     Serial.println();
    Serial.println("I sleep.");
     Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |- c -| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");



    delay(1000);
    Serial.println();
    Serial.println();
    Serial.println();
}



void Switchreader() {
//based off of arduino example code
    if (!ModbusRTUClient.requestFrom(42, DISCRETE_INPUTS, 0x00, 8)) {
        Serial.println(ModbusRTUClient.lastError());
    } 
    else {
        int n = 0;
        while (ModbusRTUClient.available() && n < 8) {
           switches[n] = ModbusRTUClient.read();
           n++;
        }
    }
}

void Relayreader() {
//based off of arduino example code for coilred
    if (!ModbusRTUClient.requestFrom(42, COILS, 0x00, 2)) {
        Serial.print("CHECK RELAYS - ERROR");
        Serial.println(ModbusRTUClient.lastError());
    } 
    else {
        int n = 0;
        while (ModbusRTUClient.available() && n < 2) {
           relays[n] = ModbusRTUClient.read();
           n++;
        }
    }
}

/* To test this code, I set the coil values in the server to 0 to see if it was
actually reading the COIL. In the video it shows that they are false. 
in the user's test, they should show up as true since I put D0 and D1 back as the
data to be read.
*/