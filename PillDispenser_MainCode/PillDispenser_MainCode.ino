#define BuzzerPin 13
// Define touch-sensitive pins and their corresponding names
const int touchPins[] = { 4, 15, 12, 33, 32 };  // GPIO numbers for T0, T3, T5, T8, T9
const char* touchPinNames[] = { "TPAD #1", "TPAD #2", "TPAD #3", "TPAD #4", "TPAD #5" };

// Threshold value for touch detection
const int threshold = 20;

// Array to store the previous touch states
bool wasTouched[] = { false, false, false, false, false };

void setup() {
  Serial.begin(115200);
  delay(1000);  // Allow time to initialize Serial Monitor
  Serial.println("ESP32 Touch Detection Initialized");
  PushButton_setup();
  Serial.println("Push Button Initialized");

  LEDS_setup();
  pinMode(BuzzerPin, OUTPUT);
  digitalWrite(BuzzerPin, LOW);
}

void loop() {
  PushButton_loop();
  LEDS_loop();
  for (int i = 0; i < 5; i++) {
    int touchValue = touchRead(touchPins[i]);
    bool isTouched = touchValue < threshold;

    // Check for a change in touch state
    if (isTouched && !wasTouched[i]) {
      Serial.print("Touch detected on ");
      Serial.println(touchPinNames[i]);
    }

    // Update the previous touch state
    wasTouched[i] = isTouched;
  }
  delay(100);  // Adjust the delay as needed
}
