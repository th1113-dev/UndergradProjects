unsigned long previousMillis = 0;
const int ledPin = 7;
int ledState = LOW;
const long interval = 1000;


void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval){
previousMillis = currentMillis;
if (ledState == LOW) {
  ledState = HIGH;
}
else{
  ledState = LOW;
}
digitalWrite(ledPin, ledState);
  }
  
  // put your main code here, to run repeatedly:

}
