#include "DHT.h"
#include <LiquidCrystal.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE); //Set up sensor

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

int red = 7;
int green = 6;
int blue = 5;
int R = 0;
int G = 0;
int B = 0;

int yellow = A5;
int Y = 0;

int white = A1;

#define TRIG_PIN 3
#define ECHO_PIN 4

void setup() {
   pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  pinMode(yellow, OUTPUT);

  pinMode(white, OUTPUT);

lcd.begin(16, 2);
lcd.setCursor(0, 0);
lcd.print("Temp C, humi %");
lcd.setCursor(0, 1);
lcd.print("Distance cm");
Serial.begin(9600);
pinMode(TRIG_PIN, OUTPUT);
pinMode(ECHO_PIN, INPUT);


dht.begin(); //Initialize the sensor
delay(1000); //Wait the finishing of the sensor initialization for 1 sec
}

void loop() {
float tempC = dht.readTemperature(); // read temperature

float humi = dht.readHumidity(); // read humidity

digitalWrite(TRIG_PIN,LOW); 
delayMicroseconds(2);
digitalWrite(TRIG_PIN,HIGH); 
delayMicroseconds(10);
digitalWrite(TRIG_PIN,LOW);
float duration = pulseIn(ECHO_PIN,HIGH);
float distance = duration*0.034/2.0; //cm

if (isnan(tempC) || isnan(humi)) {
Serial.println("Failed to read from DHT sensor!");

delay(500);
return;
}
else {
Serial.print("Temp: ");
Serial.print(tempC);
Serial.print("°C ");
Serial.print(" | ");
Serial.print("Humidity: ");
Serial.print(humi);
Serial.println("%");
Serial.print(" | ");
Serial.print("Distance: ");
Serial.print(distance);
Serial.println("cm");
}

//Display temp.
lcd.setCursor(0,0);
lcd.print("T ");
lcd.print(tempC,1);
lcd.print("C ");
lcd.print("H ");
lcd.print(humi,1);
lcd.print("%");

//Display humidity
lcd.setCursor(0,1);
lcd.print("Dist: ");
lcd.print(distance,1);
lcd.print(" cm");

if (distance < 10) {
  digitalWrite(yellow, HIGH);
  delay(100);
  digitalWrite(yellow, LOW);
  delay(50);
}
else if (distance >= 10  && distance <= 20) {
  digitalWrite(yellow, HIGH);
  delay(500);
  digitalWrite(yellow, LOW);
  delay(100);
}
else if (distance > 20 && distance <= 35) {
  digitalWrite(yellow, HIGH);
   delay(1000);
  digitalWrite(yellow, LOW);
  delay(200);
}

else {
  digitalWrite(yellow, HIGH);
}


if (humi > 50) {
  digitalWrite(white, HIGH);
  delay(1000);
  digitalWrite(white, LOW);
  delay(1000);
}
else {
  digitalWrite(white, LOW);
}
//Display temp with RBG
if (tempC < 20){
  B = 255;
  R = 0;
  G = 0;

}
else if (tempC > 25) {
  B = 0;
  R = 255;
  G = 0;
 
}

else {
  B = 0;
  R = 0;
  G = 255;
  
}
  analogWrite(red,R);
  analogWrite(blue,B);
  analogWrite(green,G);
delay(500);
}


