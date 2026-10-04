const int analogPin = 1;
const int ledPin = 11;


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  int inputValue = analogRead(analogPin);
  float volt = inputValue*5.0/1023.0;
  Serial.print("Input Volt: ");
  Serial.println(volt);

  int outputValue = inputValue*255.0/1023.0;

  Serial.print("output PWM duty cucle scale: ");
  Serial.println(outputValue);

  analogWrite(ledPin, outputValue);

  delay(1000);
  // put your main code here, to run repeatedly:

}
