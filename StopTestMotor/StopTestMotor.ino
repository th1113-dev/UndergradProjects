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

void loop() { //---back and forth example
Serial.println("One way, then reverse and slow stop: ");
digitalWrite(ENABLE,HIGH); // enable on motor control
digitalWrite(DIRA,HIGH); //one way rotation at full speed
digitalWrite(DIRB,LOW); 
delay(2000);

digitalWrite(DIRA,LOW); //reverse way rotation at full speed
digitalWrite(DIRB,HIGH); 
delay(2000);

Serial.println("Soft braking");
digitalWrite(DIRA,LOW); 
digitalWrite(DIRB,LOW); 
digitalWrite(ENABLE,LOW); // soft brake for slow motor stop
delay(3000);

Serial.println("One way rotation, then fast stop: ");
digitalWrite(ENABLE,HIGH); //enable on motor control
digitalWrite(DIRA,HIGH); 
digitalWrite(DIRB,LOW); //one way rotation at full speed
delay(2000);

Serial.println("Hard braking");
digitalWrite(DIRA,HIGH); 
digitalWrite(DIRB,HIGH); //hard brake for fast motor stop
delay(500);

digitalWrite(DIRA,LOW); 
digitalWrite(DIRB,LOW); 
digitalWrite(ENABLE,LOW); //enable off
delay(3000);

Serial.println("One way rotation, then fastest stop: ");
digitalWrite(ENABLE,HIGH); //enable on motor control
digitalWrite(DIRA,HIGH); 
digitalWrite(DIRB,LOW); //one way rotation at full speed
delay(2000);

Serial.println("Hardest braking");
digitalWrite(DIRA,LOW); 
digitalWrite(DIRB,HIGH); //hardest brake for fastest motor stop
delay(70);

digitalWrite(DIRA,LOW); 
digitalWrite(DIRB,LOW); 
digitalWrite(ENABLE,LOW); //enable off
delay(3000);
}

