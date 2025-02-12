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

DS3231 myRTC;

#define BuzzerPin 13






int CurrentCompartment = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("System Start...");
  delay(1000);  // Allow time to initialize Serial Monitor

  Wire.begin();  // SDA, SCL pins for ESP32
  RTC_PrintTime();
  //SET DATE & TIME
  //DS3231_setTime(12, 30, 0, 2, 12, 25);  //Hour-Minute-Second-Month-Date-Year (24HR FORMAT)



  Touch_setup();
  RTC_PrintTime();
  LEDS_setup();
  RTC_PrintTime();
  Servo_setup();
  RTC_PrintTime();

  PushButton_setup();
  RTC_PrintTime();

  pinMode(BuzzerPin, OUTPUT);
  digitalWrite(BuzzerPin, LOW);
}

void loop() {
  PushButton_loop();
  Touch_loop();
  //RTC_PrintTime();
}


void Goto_Compartment(int ThisCompartment) {
  while (CurrentCompartment != ThisCompartment) {

    Servo_Move60();
    delay(1000);
  }
}