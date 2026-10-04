/*  OPTA tutorial #2
    Name: OPTA_Button_test
    Purpose: Test Button and configure ot to control the STATUS LED on the OPTA

    Author: ARDUIO
    Student: Theodis Hill (UID:118983264)
*/
int buttonState = 0;
int counter = 0;

void setup() {
  pinMode(LED_D0, OUTPUT);
  pinMode(LED_D1, OUTPUT);
  pinMode(LED_D2, OUTPUT);
  pinMode(LED_D3, OUTPUT);
  pinMode(BTN_USER, INPUT);
}

void loop() {
  buttonState = digitalRead(BTN_USER);
  if(buttonState == LOW){
    if(counter < 4){
      counter++;
    }
    else{
      counter = 0;
    }
    delay(100);
  }
  changeLights();
}

void changeLights(){
  switch(counter){
    case 0:
      digitalWrite(LED_D0, LOW);
      digitalWrite(LED_D1, LOW);
      digitalWrite(LED_D2, LOW);
      digitalWrite(LED_D3, LOW);
      break;
    case 1:
      digitalWrite(LED_D0, HIGH);
      break;
    case 2:
      digitalWrite(LED_D1, HIGH);
      break;
    case 3:
      digitalWrite(LED_D2, HIGH);
      break;
    case 4:
      digitalWrite(LED_D3, HIGH);
      break;
  }
  delay(100);
}
//works :)