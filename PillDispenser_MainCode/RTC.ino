

void RTC_setup() {
  Wire.begin(21, 22);  // SDA, SCL pins for ESP32

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1)
      ;
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting the time!");
    // Set the RTC to the current date and time
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void RTC_PrintTime() {
  DateTime now = rtc.now();
  Serial.print("Current Time: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
}