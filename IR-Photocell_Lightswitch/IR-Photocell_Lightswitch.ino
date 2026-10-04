#include "IRremote.h"
#include "IR-3.h"

#define IR_PIN 11
#define LED_PIN 12  // Changed from 9 to 6 to avoid Timer 2 conflict
#define LDR_PIN A0

IRrecv irrecv(IR_PIN);
decode_results results;

bool ledState = false;
int brightness = 120; // Increased default so it's visible immediately

int ldrThreshold = 400;
bool lastLdrDetect = false;
unsigned long lastToggleTime = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  // ---------- PHOTOCELL TOGGLE ----------
  int ldrValue = analogRead(LDR_PIN);
  bool fingerDetected = ldrValue < ldrThreshold;

  if (fingerDetected && !lastLdrDetect && millis() - lastToggleTime > 300) {
    ledState = !ledState;
    lastToggleTime = millis();
  }
  lastLdrDetect = fingerDetected;

  // ---------- IR REMOTE ----------
  if (irrecv.decode(&results)) {
    if (results.value != 0xFFFFFFFF) { 
       switch (results.value) {
          case KEY_POWER:
              ledState = !ledState;
              break;
          case KEY_UP:
              if (ledState) brightness = min(brightness + 15, 255);
              break;
          case KEY_DOWN:
              if (ledState) brightness = max(brightness - 15, 0);
              break;
       }
    }
    irrecv.resume(); // Receive the next value
  }

  // ---------- APPLY OUTPUT ----------
  if (ledState) {
    analogWrite(LED_PIN, brightness);
  } else {
    analogWrite(LED_PIN, 0);
  }
}

