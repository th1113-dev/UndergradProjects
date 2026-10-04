volatile unsigned int counter, relayLedState {};
volatile bool relCntState = false;
volatile bool batchState01 = false;
volatile bool batchState23 = false;


void setup() {
  for (int i = 0; i < 4; i++){
    pinMode(relays[i], OUTPUT);
    pinMode(leds[i], OUTPUT);
  }


pinMode(A0, INPUT);
pinMode(A1, INPUT);
pinMode(BTN_USER, INPUT);

attachInterrupt(digitalPinToInterrupt(BTN_USER), relayCounterISR, RISING);
attachInterrupt(digitalPinToInterrupt(A0), batch01_ISR, RISING);
attachInterrupt(digitalPinToInterrupt(A1), batch23_ISR, RISING);
}

void loop() {
  if (millis() > printNow) {
    Serial.print("Presses: ");
    Serial.println(counter);

    printNow = millis() + printInterval;
  }

  relayLinearCounter();

  relayBatchInverter();
}

/**
  Function to manage relay and status LED state in linear sequence based on BTN_USER interrupt.
*/
void relayLinearCounter(){
  if (relCntState == true){
    if (counter > 4){
      relayLedState = counter % 4;
      
      if (relayLedState == 0){
        relayLedState = 4;
      }
    } else {
      relayLedState = counter;      
    }

    Serial.print(F("Triggered Relay: "));
    Serial.println(relayLedState);
    Serial.print(F("Counter Status: "));
    Serial.println(counter);

    // Array indexes start at 0
    idx = relayLedState - 1;
    relayStateHandler(idx);

    relCntState = false;
  }
}

/**
 Function to handle relay and status LED states based on A0 & A1 interrupts to invert its defined states in batch.
*/
void relayBatchInverter(){
  if (batchState01 == true){
    Serial.println(F("A0 interrupt: Relay Batch 0 & 1"));
    for (int i = 0; i < 2; i++){
      relayStateHandler(i);
    }
    batchState01 = false;
  }

  if (batchState23 == true){
    Serial.println(F("A1 interrupt: Relay Batch 2 & 3"));
    for (int j = 2; j < 4; j++){
      relayStateHandler(j);
    }
    batchState23 = false;
  }
}

