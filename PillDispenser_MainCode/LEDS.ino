

void LEDS_setup(){
  Serial.println("LEDS Initialize...");
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, HIGH);
}

void LEDS_SetStatus(int ThisLED, bool Status){
  if (Status){
    digitalWrite(ThisLED, LOW);
  } else {
    digitalWrite(ThisLED, HIGH);
  }
}




void LEDS_test(){
  digitalWrite(LED1, LOW);
  delay(100);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  delay(100);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, LOW);
  delay(100);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, LOW);
  delay(100);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, LOW);
  delay(100);
  digitalWrite(LED5, HIGH);
}