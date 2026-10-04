int led = 7;
int brightness = 0;
int fading = 5;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
analogWrite(led, brightness);

brightness = brightness + fading;

if (brightness <= 0 || brightness >= 255) {
  fading = -fading;
}
delay(15);
}
