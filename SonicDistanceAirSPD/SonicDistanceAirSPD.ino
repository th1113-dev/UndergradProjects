#define TRIG_PIN 13
#define ECHO_PIN 10

void setup() {
Serial.begin(9600);
pinMode(TRIG_PIN, OUTPUT);
pinMode(ECHO_PIN, INPUT);
delay(1000);
}

void loop() {
digitalWrite(TRIG_PIN,LOW); delayMicroseconds(2);
digitalWrite(TRIG_PIN,HIGH); delayMicroseconds(10);
digitalWrite(TRIG_PIN,LOW);
float duration=pulseIn(ECHO_PIN,HIGH);
float distance=duration*0.034/2.0; //cm
Serial.print(distance); Serial.println("cm");
delay(500);
}
