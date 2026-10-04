/**
   Arduino Timing drift

   Copyright (C) 2025, Nicholas Limparis University of Maryland.
   Released under the MIT License.
*/

#include <LiquidCrystal.h>
//#include <Adafruit_LiquidCrystal.h>

// Pin Number Definitions
#define LCD_BL 4
#define LCD_D4 10
#define LCD_D5 9
#define LCD_D6 8
#define LCD_D7 7
#define LCD_EN 11
#define LCD_RS 12

#define DIST_TRIG 6
#define DIST_ECHO 5

#define LED_1 A1
#define LED_2 A2
#define LED_3 A3
//#define LED4 A4

#define BUTTON 2

// Global Variables
int seconds = 0;

int Ditance s= 0;

int BUTTONIN = 0;
bool BUTTONSTATE = false;

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7); //Define the LCD object

// Local Function Definitions
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}


// System Initialization
void setup()
{
  lcd.begin(16, 2);
  // Set Pin Directions
  pinMode(LED_BUILTIN, OUTPUT); // Used to count Half seconds
  pinMode(LCD_BL, OUTPUT); // Used to turn the backlight on and off
  // LED Pin Directions
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  //pinMode(LED_4, OUTPUT);
  // Button Pin
  pinMode(BUTTON, INPUT);
  //LCD Setup
  digitalWrite(LCD_BL,HIGH); // Turn the BL on
  lcd.clear();
  lcd.print("hello world");
  delay(3000); // Wait for 3000 millisecond(s)
}

// Main Loop

void loop()
{
  // Setup the LCD for display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Time: ");
  lcd.print(seconds);
  lcd.print(" s");
  lcd.setCursor(0, 1);
  lcd.print("Distance: ");
  lcd.print(Distance);
  lcd.print(" cm");

  // "Running" LEDs changeing state every 125 ms
  delay(125); // wait 125 ms
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  
  delay(125);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, HIGH);
  digitalWrite(LED_3, LOW);
  
  delay(125);
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);
  digitalWrite(LED_3, LOW);
  
  delay(125); //  .5 SEC 
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, HIGH);
  
  //digitalWrite(LED_BUILTIN, HIGH);
  delay(125); // Wait for 125 millisecond(s)
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, HIGH);
  
  delay(125); // Wait for 125 millisecond(s)
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, HIGH);
  digitalWrite(LED_3, HIGH);
  
  delay(125);
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);
  digitalWrite(LED_3, HIGH);
  
  delay(125); // 1 second
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, HIGH);
  digitalWrite(LED_3, LOW);
  
  
  seconds += 1;
  // update distance from sensor
  Distance = 0.01723 * readUltrasonicDistance(DIST_TRIG, DIST_ECHO);

  // Check Button
  BUTTONIN =  digitalRead(BUTTON); 
  if (BUTTONIN == 0){
    BUTTONSTATE = true;
  }
  else{
    BUTTONSTATE = false;
  }
  digitalWrite(LED_BUILTIN, BUTTONSTATE);

}
