#include <HCSR04.h>
#define TRIG_PIN 13
#define ECHO_PIN 10
UltraSonicDistanceSensor distanceSensor(TRIG_PIN,ECHO_PIN);

void setup() {
Serial.begin(9600);
delay(1000);
}

void loop() {
float distance = distanceSensor.measureDistanceCm();
Serial.print(distance);
Serial.println("cm");
delay(500);
}
