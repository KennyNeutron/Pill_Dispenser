#define PB1 21
#define PB2 22


void PushButton_setup(){
  pinMode(PB1, INPUT_PULLUP);
  pinMode(PB2, INPUT_PULLUP);
}


void PushButton_loop(){
  if(digitalRead(PB1) == LOW){
    Serial.println("PB1 pressed");
    digitalWrite(BuzzerPin, HIGH);
  }
  if(digitalRead(PB2) == LOW){
    Serial.println("PB2 pressed");
    digitalWrite(BuzzerPin, HIGH);
  }

  if(digitalRead(PB1) && digitalRead(PB2)){
    digitalWrite(BuzzerPin, LOW);
  }
}