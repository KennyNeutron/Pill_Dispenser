// ============================
// ESP32 BOARD CONFIGURATION
// ============================
// CPU Frequency: 240MHz (WiFi/BT Enabled) - Maximizes performance
// Flash Frequency: 40MHz - Default and stable for most ESP32 modules
// Flash Mode: QIO - Faster flash read/write operations
// Flash Size: 4MB (32Mb) - Sufficient for this project
// Partition Scheme: Default 4MB with SPIFFS (1.2MB APP / 1.5MB SPIFFS)
// PSRAM: Disabled - No extra external RAM available
// JTAG: Disabled - Debugging via serial only
// Upload Speed: 921600 - Fastest stable upload speed
// Events & Arduino Core Runs on Core 1 - Avoids conflicts with WiFi tasks on Core 0
// Zigbee Mode: Disabled - No Zigbee support in this project
// ============================

#include <Wire.h>
#include "DS3231.h"
#include <HardwareSerial.h>
#include <Arduino.h>

DS3231 myRTC;

#define BuzzerPin 13
#define LED1 14
#define LED2 27
#define LED3 26
#define LED4 25
#define LED5 23


byte year;
byte month;
byte date;
byte dow;
byte hour;
byte minute;
byte second;

bool century = false;
bool h12Flag;
bool pmFlag;


bool Sched_4Hr = false;
bool Sched_6Hr = false;
bool Sched_8Hr = false;
bool Sched_12Hr = false;
bool Sched_24Hr = false;

bool Notify_4Hr = false;
bool Notify_6Hr = false;
bool Notify_8Hr = false;
bool Notify_12Hr = false;
bool Notify_24Hr = false;


int CurrentCompartment = 0;


bool Notified = false;
bool TellTime = true;
bool DispenseStarted = false;

void setup() {
  Serial.begin(115200);
  Serial.println("System Start...");
  delay(1000);  // Allow time to initialize Serial Monitor

  Wire.begin();  // SDA, SCL pins for ESP32
  RTC_PrintTime();
  //SET DATE & TIME
  DS3231_setTime(5, 59, 30, 2, 12, 25);  //Hour-Minute-Second-Month-Date-Year (24HR FORMAT)

  Touch_setup();
  RTC_PrintTime();
  LEDS_setup();
  RTC_PrintTime();
  Servo_setup();
  RTC_PrintTime();

  PushButton_setup();
  RTC_PrintTime();

  GSM_setup();
  RTC_PrintTime();

  pinMode(BuzzerPin, OUTPUT);
  digitalWrite(BuzzerPin, LOW);

  LEDS_test();
  Sched_4Hr = false;
  Sched_6Hr = false;
  Sched_8Hr = false;
  Sched_12Hr = false;
  Sched_24Hr = false;
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, HIGH);
  
}

void loop() {
  PushButton_loop();
  Touch_loop();
  PillDispense();
  if (TellTime) {
    RTC_PrintTime();
  }
}




void PillDispense() {
  Check_Notif();
  if (Notify_4Hr) {
    Serial.println("NOTIFY!");
    delay(1000);
    Goto_Compartment(1);
    sendSMS("Schedule for your 4-Hour Pill/Meds Please take your pill/meds now...");
    digitalWrite(BuzzerPin, HIGH);
    Notify_4Hr = false;
    TellTime = false;
    while (!TellTime) {
      Reset_PB();
    }
  }

  if (Notify_6Hr) {
    Serial.println("NOTIFY!");
    delay(1000);
    Goto_Compartment(2);
    sendSMS("Schedule for your 6-Hour Pill/Meds Please take your pill/meds now...");
    digitalWrite(BuzzerPin, HIGH);
    Notify_6Hr = false;
    TellTime = false;
  }

  if (Notify_8Hr) {
    Serial.println("NOTIFY!");
    delay(1000);
    Goto_Compartment(3);
    sendSMS("Schedule for your 8-Hour Pill/Meds Please take your pill/meds now...");
    digitalWrite(BuzzerPin, HIGH);
    Notify_8Hr = false;
    TellTime = false;
  }

  if (Notify_12Hr) {
    Serial.println("NOTIFY!");
    delay(1000);
    Goto_Compartment(4);
    sendSMS("Schedule for your 12-Hour Pill/Meds Please take your pill/meds now...");
    digitalWrite(BuzzerPin, HIGH);
    Notify_12Hr = false;
    TellTime = false;
  }

  if (Notify_24Hr) {
    Serial.println("NOTIFY!");
    delay(1000);
    Goto_Compartment(5);
    sendSMS("Schedule for your 24-Hour Pill/Meds Please take your pill/meds now...");
    digitalWrite(BuzzerPin, HIGH);
    Notify_24Hr = false;
    TellTime = false;
  }
}


void Check_Notif() {
  if (Sched_4Hr && get_Sched4Hr() && myRTC.getMinute() == 0 && myRTC.getSecond() == 0) {
    Notify_4Hr = true;
  }

  if (Sched_6Hr && get_Sched6Hr() && myRTC.getMinute() == 0 && myRTC.getSecond() == 0) {
    Notify_6Hr = true;
  }

  if (Sched_8Hr && get_Sched8Hr() && myRTC.getMinute() == 0 && myRTC.getSecond() == 0) {
    Notify_8Hr = true;
  }

  if (Sched_12Hr && get_Sched12Hr() && myRTC.getMinute() == 0 && myRTC.getSecond() == 0) {
    Notify_12Hr = true;
  }

  if (Sched_24Hr && get_Sched24Hr() && myRTC.getMinute() == 0 && myRTC.getSecond() == 0) {
    Notify_24Hr = true;
  }
}


bool get_Sched4Hr() {
  if (myRTC.getHour(h12Flag, pmFlag) == 0 || myRTC.getHour(h12Flag, pmFlag) == 4 || myRTC.getHour(h12Flag, pmFlag) == 8 || myRTC.getHour(h12Flag, pmFlag) == 12 || myRTC.getHour(h12Flag, pmFlag) == 16 || myRTC.getHour(h12Flag, pmFlag) == 20) {
    return true;
  } else {
    return false;
  }
}

bool get_Sched6Hr() {
  if (myRTC.getHour(h12Flag, pmFlag) == 0 || myRTC.getHour(h12Flag, pmFlag) == 6 || myRTC.getHour(h12Flag, pmFlag) == 12 || myRTC.getHour(h12Flag, pmFlag) == 18) {
    return true;
  } else {
    return false;
  }
}

bool get_Sched8Hr() {
  if (myRTC.getHour(h12Flag, pmFlag) == 0 || myRTC.getHour(h12Flag, pmFlag) == 8 || myRTC.getHour(h12Flag, pmFlag) == 16) {
    return true;
  } else {
    return false;
  }
}


bool get_Sched12Hr() {
  if (myRTC.getHour(h12Flag, pmFlag) == 6 || myRTC.getHour(h12Flag, pmFlag) == 18) {
    return true;
  } else {
    return false;
  }
}


bool get_Sched24Hr() {
  if (myRTC.getHour(h12Flag, pmFlag) == 6) {
    return true;
  } else {
    return false;
  }
}