/**
  Getting Started with Opta™
  Name: Analog_Inputs_Opta
  Purpose: Test analog pins A0, A1 and A2 as inputs on Opta™.

  @author Arduino
  student:Theodis Hill (UID:118983264)
*/

void setup() {
   Serial.begin(9600);
   // 65535 is the max value with 16 bits resolution set by analogReadResolution(16)
   // 4095 is the max value with 12 bits resolution set by analogReadResolution(12)
   analogReadResolution(12);
}

void loop() {
   // Read the input on analog input I1 corresponding to A0:
   int sensorValueA0 = analogRead(A0);
   float voltageA0 = sensorValueA0 * (3.0 / 4095.0)/ 0.3;

   // Print out the value you read from I1 to the max value for the analog inputs resolution:
   Serial.print("I1 value: ");
   Serial.print(sensorValueA0);
   Serial.print(" corresponding to ");
   Serial.print(voltageA0, 5);
   Serial.print("Volts");

    int sensorValueA1 = analogRead(A1);
   float voltageA1 = sensorValueA1 * (3.0 / 4095.0)/ 0.3;

   // Print out the value you read from I1 to the max value for the analog inputs resolution:
   Serial.print("I2 value: ");
   Serial.print(sensorValueA1);
   Serial.print(" corresponding to ");
   Serial.print(voltageA1, 5);
   Serial.print("Volts");

    int sensorValueA2 = analogRead(A2);
   float voltageA2 = sensorValueA2 * (3.0 / 4095.0)/ 0.3;

   // Print out the value you read from I1 to the max value for the analog inputs resolution:
   Serial.print("I3 value: ");
   Serial.print(sensorValueA2);
   Serial.print(" corresponding to ");
   Serial.print(voltageA2, 5);
   Serial.print("Volts");

   delay(1000);
}
//Works :)