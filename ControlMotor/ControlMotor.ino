#define ENABLE 5
#define DIRA 3
#define DIRB 4

const float MaxV = 5.0;
const float deadband = 1.2;

void setup() {
pinMode(ENABLE,OUTPUT); 
pinMode(DIRA,OUTPUT);
pinMode(DIRB,OUTPUT); 
Serial.begin(9600);

Serial.println("Please enter a motor voltage from -5 to +5 volts:");
}

void loop() {
if (Serial.available() > 0) {
  float inputV = Serial.parseFloat();

  while (Serial.available()) Serial.read();

  Serial.print("Recieved voltage: ");
  Serial.println(inputV);

  if (abs(inputV) < deadband){
    digitalWrite(ENABLE, HIGH);
    digitalWrite(DIRA, HIGH);
    digitalWrite(DIRB, HIGH);
    Serial.println("Motor Direction: Stop");
    return;
  }
  
  float normalized = abs(inputV) / MaxV;
  
  if (normalized > 1.0) normalized = 1.0;
  
  int dutyCycle = (int)(normalized * 255);

  if (inputV > 0) {
     digitalWrite(ENABLE, HIGH);
    digitalWrite(DIRA, HIGH);
    digitalWrite(DIRB, LOW);
    Serial.println("Motor Direction: Forward");
    return;
  }
  else {
   digitalWrite(ENABLE, HIGH);
    digitalWrite(DIRA, LOW);
    digitalWrite(DIRB, HIGH);
    Serial.println("Motor Direction: Backwards");
    return;
  }

  Serial.print("PWM Duty Cylcle: ");
  Serial.print(dutyCycle);
}
}
