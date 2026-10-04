int red = 7;
int green = 6;
int blue = 5;
int R = 255;
int G = 0;
int B = 0;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {

for (int bright = 0; bright <=250; bright++){
  R = 255 - bright;
  G = bright;
  B = 0;
analogWrite(red, R);
analogWrite(green, G);
analogWrite(blue, B);
delay(60);
}
for (int bright = 0; bright <=250; bright++){
  G = 255 - bright;
  B = bright;
  R = 0;
analogWrite(red, R);
analogWrite(green, G);
analogWrite(blue, B);
delay(30);
}
for (int bright = 0; bright <=250; bright++){
  B = 255 - bright;
  R = bright;
  G = 0;
analogWrite(red, R);
analogWrite(green, G);
analogWrite(blue, B);
delay(60);
}

}
