const int LIGHTBULB = A0; 

void setup() {
Serial.begin(9600);
}

void loop() {
  
  int value;



  float volt;

  value = analogRead(LIGHTBULB);


  volt = value * 5.0/1023.0;
  Serial.print("Value: :");
  Serial.print(value);
  Serial.print(" Volt: ");
  Serial.println(volt);

  delay(500);
}

// Almost identical to Example 1 code. Two wires are plugged into 5V and GND and the last wire is plugged between the Resistor and Bulb.
// The Voltage input is read as a constant Integer, "LIGHTBULB" and is plugged in A0.
// In setup, I set the Serial.Begin to 9600 to indicate 10-Bit ADC conversion.
// In the loop I set the integer "value" equal to the read analogue outputs of LIGHTBULB every 500 time inputs.
// The float value, "volt" is determined by value multiplied to The reference voltage(5Volts) over the Max ADC reading(1023). 
// The code then reads off value and then the inputs that into the voltage equation. 
// Finally, the calculated voltage is output.