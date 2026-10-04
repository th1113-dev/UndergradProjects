#include <LiquidCrystal.h>
#include <HCSR04.h>
#include <TimerOne.h>

#define LCD_BL 4
#define LCD_D4 10
#define LCD_D5 9
#define LCD_D6 8
#define LCD_D7 7
#define LCD_EN 11
#define LCD_RS 12

#define TRIG_PIN 6
#define ECHO_PIN 5

#define LED_1 A1
#define LED_2 A2
#define LED_3 A3
//#define LED4 A4

#define BUTTON 2

// Global Variables
int seconds = 0;

int Distance = 0;


int state1 = LOW;
int state2 = LOW;
int state3 = LOW;

int BUTTONIN = 0;
bool BUTTONSTATE = false;

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7); //Define the LCD object
// Local Function Definitions
long readUltrasonicDistance(TRIG_PIN, ECHO_PIN);

void BlinkShow(){ //Learned about State Machine approaches using bit logic for this
static int WhatState = 0;
WhatState = (WhatState + 1) % 8; 
state1 = (WhatState & 0x01);
state2 = (WhatState & 0x02);
state3 = (WhatState & 0x04);

digitalWrite(LED_1, state1);
digitalWrite(LED_2, state2);
digitalWrite(LED_3, state3);
}

void secunda(){
  seconds += 1;
}

void screenUpdate(){
 lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Time: ");
  lcd.print(seconds);
  lcd.print(" s");
  lcd.setCursor(0, 1);
  lcd.print("Distance: ");
  lcd.print(Distance);
  lcd.print(" cm");
}

void setup() {
lcd.begin(16, 2);
 
  pinMode(LED_BUILTIN, OUTPUT); // Used to count Half seconds
  pinMode(LCD_BL, OUTPUT); // Used to turn the backlight on and off

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  Timer1.initialize(125000); //Will interrupt every 125 ms
  Timer1.attachInterrupt(BlinkShow);
  Serial.begin(9600);

  Timer1.initialize(100000000); //Will interrupt every 1 sec
  Timer1.attachInterrupt(secunda);
    Serial.begin(9600);

  Timer1.initialize(500000); //Will interrupt every 500 ms
  Timer1.attachInterrupt(screenUpdate);
  Serial.begin(9600);

pinMode(BUTTON, INPUT);
  //LCD Setup
  digitalWrite(LCD_BL,HIGH); // Turn the BL on
  lcd.clear();
  lcd.print("hello world");
  delay(3000); 
}

void bottonPress(){ // Need to find a way to make this update instantaneously
   for(buttonState = digital.read(BUTTON)){
    if(buttonState == LOW){
      BUTTONSTATE = true;
    }
    else{
      BUTTONSTATE = false;
    }
  digitalWrite(LED_BUILTIN, BUTTONSTATE);
   }
}

void loop() {
    // update distance from sensor
digitalWrite(TRIG_PIN,LOW); delayMicroseconds(2);
digitalWrite(TRIG_PIN,HIGH); delayMicroseconds(10);
digitalWrite(TRIG_PIN,LOW);
float duration=pulseIn(ECHO_PIN,HIGH);
float distance=duration*0.034/2.0; //cm

}

