
void PushButton_setup() {
  Serial.println("Push Button Initialize...");
  pinMode(PB1, INPUT_PULLUP);
  pinMode(PB2, INPUT_PULLUP);
}


void PushButton_loop() {
  if (PushButton_GetStatus_PushButton1() && !PB_Toggle) {
    Serial.println("PB1 pressed");
    delay(100);
    PB_Toggle = true;
    PB_Pressed = 1;
  }

  if (PushButton_GetStatus_PushButton2() && !PB_Toggle) {
    Serial.println("PB2 pressed");
    delay(100);
    PB_Toggle = true;
    PB_Pressed = 2;
    TellTime=true;
  }

  if (!PushButton_GetStatus_PushButton1() && !PushButton_GetStatus_PushButton2() && PB_Toggle) {
    PB_Toggle = false;
    PB_Function = false;
    PB_Pressed = 0;
    myServo.write(STOP);
  }


  if (PB_Pressed == 1 && PB_Toggle && !PB_Function) {
    delay(100);
    Serial.println("PB1 pressed");
    Servo_Move60();
    PB_Function = true;
  }

  Reset_PB();
}

bool PushButton_GetStatus_PushButton1() {
  if (digitalRead(PB1) == LOW) {
    return true;
  } else {
    return false;
  }
}

bool PushButton_GetStatus_PushButton2() {
  if (digitalRead(PB2) == LOW) {
    return true;
  } else {
    return false;
  }
}


void Reset_PB(){
    if (PB_Pressed == 2 && PB_Toggle && !PB_Function) {
    delay(100);
    Serial.println("PB2 pressed");

    

    Goto_Compartment(0);
    PB_Function = true;
    delay(1000);
    //sendSMS("Pill Dispenser Reset to Default Compartment");
    digitalWrite(BuzzerPin, LOW);
    Notified=false;
  }
}