#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

#define BuzzerPin 13






int CurrentCompartment = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);  // Allow time to initialize Serial Monitor
  RTC_setup();
  Touch_setup();
  PushButton_setup();
  LEDS_setup();
  Servo_setup();

  pinMode(BuzzerPin, OUTPUT);
  digitalWrite(BuzzerPin, LOW);

  RTC_PrintTime();
}

void loop() {
  PushButton_loop();
  Touch_loop();
}


void Goto_Compartment(int ThisCompartment) {
  while (CurrentCompartment != ThisCompartment) {

    Servo_Move60();
    delay(1000);
  }
}