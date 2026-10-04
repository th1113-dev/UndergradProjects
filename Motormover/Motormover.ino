#include <LiquidCrystal.h> 
#include <Servo.h>

// Initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Servo myServo;
const int servoPin = 3;
const int joyY = A1;

// Custom character for the bar graph (Diamond/Spade style)
byte styleChar[8] = {
  B00000, B00100, B01110, B11111, B11111, B01110, B00100, B00000
};

int lastAngle = -1;       // Track changes to reduce wire noise
unsigned long lastRefresh = 0; 
int hardResetCounter = 0;

void setup() {
  myServo.attach(servoPin);
  setupLCD();
}

void setupLCD() {
  lcd.begin(16, 2);
  lcd.createChar(0, styleChar);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Servo Stabilized");
  delay(500);
}

void loop() {
  int yVal = analogRead(joyY);
  
  // Map Joystick to Servo Angle
  int currentAngle = map(yVal, 0, 1023, 0, 180);
  
  // Noise Filter: Only move servo if change is > 1 degree (prevents jitter)
  if (abs(currentAngle - lastAngle) > 1) {
    myServo.write(currentAngle);
    lastAngle = currentAngle;
  }

  // LCD Update Timer (Every 150ms)
  if (millis() - lastRefresh > 150) {
    lastRefresh = millis();
    hardResetCounter++;

    // Force Re-init every 3 seconds to clear "haywire" symbols
    if (hardResetCounter > 20) {
      setupLCD();
      hardResetCounter = 0;
    }

    // Row 0: Angle Display
    lcd.setCursor(0, 0);
    lcd.print("Angle: ");
    lcd.print(currentAngle);
    lcd.print((char)223); // Degree symbol
    lcd.print("   ");     // Clear ghost digits

    // Row 1: Bar Graph (0-180 mapped to 0-16 blocks)
    lcd.setCursor(0, 1);
    int barLength = map(currentAngle, 0, 180, 0, 16);
    for (int i = 0; i < 16; i++) {
      if (i < barLength) lcd.write(byte(0));
      else lcd.print(" ");
    }
  }
}