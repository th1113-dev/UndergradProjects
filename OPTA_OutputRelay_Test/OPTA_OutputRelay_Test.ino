/* Name: OUTPUT Relay for OPTA
    Purpose: Test the OUTPUT Relay for the OPTA

    Author: ARDUINO
    Student: Theodis Hill (UID:118983264)
*/

void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);

   pinMode(LED_D0, OUTPUT);
   pinMode(LED_D1, OUTPUT);
   pinMode(LED_D2, OUTPUT);
   pinMode(LED_D3, OUTPUT);
}

void loop() {
  digitalWrite(D0, HIGH);
  digitalWrite(LED_D0, HIGH);
  delay(1000);
  digitalWrite(D0, LOW);
  digitalWrite(LED_D0, LOW);
  delay(1000);

  digitalWrite(D1, HIGH);
  digitalWrite(LED_D1, HIGH);
  delay(1000);
  digitalWrite(D1, LOW);
  digitalWrite(LED_D1, LOW);
  delay(1000);
  
  digitalWrite(D2, HIGH);
  digitalWrite(LED_D2, HIGH);
  delay(1000);
  digitalWrite(D2, LOW);
  digitalWrite(LED_D2, LOW);
  delay(1000);
  
  digitalWrite(D3, HIGH);
  digitalWrite(LED_D3, HIGH);
  delay(1000);
  digitalWrite(D3, LOW);
  digitalWrite(LED_D3, LOW);
  delay(1000);
  
}
//works :)