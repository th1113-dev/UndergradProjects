#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE); //Set up sensor

void setup() {
Serial.begin(9600);
dht.begin(); //Initialize the sensor
delay(1000); //Wait the finishing of the sensor initialization for 1 sec
}

void loop() {
float tempC = dht.readTemperature(); // read temperature
float humi = dht.readHumidity(); // read humidity
if (isnan(tempC) || isnan(humi)) {
Serial.println("Failed to read from DHT sensor!");
} else {
Serial.print("Temperature: ");
Serial.print(tempC);
Serial.print("°C ");
Serial.print(" | ");
Serial.print("Humidity: ");
Serial.print(humi);
Serial.println("%");
}
delay(2000); // update the results every 1 sec
}

