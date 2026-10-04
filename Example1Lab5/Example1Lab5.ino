const int VOL_PIN = A0; //Named Input pin "VOL_Pin"

void setup() {
Serial.begin(9600);
}

void loop() {
  
  int value;



  float volt;

  value = analogueRead(VOL_PIN);


  volt = value * 5.0/1023.0;


  Serial.print("Value:  :");
  Serial.print(value);
  Serial.print(" Volt: ");
  Serial.println(volt);

  delay(500);
}
