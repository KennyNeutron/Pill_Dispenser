// Define touch-sensitive pins and their corresponding names
const int touchPins[] = { 4, 15, 12, 33, 32 };  // GPIO numbers for T0, T3, T5, T8, T9
const char* touchPinNames[] = { "TPAD #1", "TPAD #2", "TPAD #3", "TPAD #4", "TPAD #5" };

// Threshold value for touch detection
const int threshold = 10;

// Array to store the previous touch states
bool wasTouched[] = { false, false, false, false, false };


void Touch_setup() {
  Serial.println("ESP32 Touch Detection Initialized");
}


void Touch_loop() {
  for (int i = 0; i < 5; i++) {
    int touchValue = touchRead(touchPins[i]);
    bool isTouched = touchValue < threshold;

    // Check for a change in touch state
    if (isTouched && !wasTouched[i]) {
      Serial.print("Touch detected on ");
      Serial.println(touchPinNames[i]);
      delay(100);
    }

    // Update the previous touch state
    wasTouched[i] = isTouched;
  }




  Touch_Functions();
}


void Touch_Functions() {
  if (wasTouched[0]) {
    Sched_4Hr = !Sched_4Hr;
    wasTouched[0] = false;
  }

  if (wasTouched[1]) {
    Sched_6Hr = !Sched_6Hr;
    wasTouched[1] = false;
  }

  if (wasTouched[2]) {
    Sched_8Hr = !Sched_8Hr;
    wasTouched[2] = false;
  }

  if (wasTouched[3]) {
    Sched_12Hr = !Sched_12Hr;
    wasTouched[3] = false;
  }

  if (wasTouched[4]) {
    Sched_24Hr = !Sched_24Hr;
    wasTouched[4] = false;
  }

  if (Sched_4Hr) {
    LEDS_SetStatus(LED1, HIGH);
  } else {
    LEDS_SetStatus(LED1, LOW);
  }

  if (Sched_6Hr) {
    LEDS_SetStatus(LED2, HIGH);
  } else {
    LEDS_SetStatus(LED2, LOW);
  }

  if (Sched_8Hr) {
    LEDS_SetStatus(LED3, HIGH);
  } else {
    LEDS_SetStatus(LED3, LOW);
  }

  if (Sched_12Hr) {
    LEDS_SetStatus(LED4, HIGH);
  } else {
    LEDS_SetStatus(LED4, LOW);
  }

  if (Sched_24Hr) {
    LEDS_SetStatus(LED5, HIGH);
  } else {
    LEDS_SetStatus(LED5, LOW);
  }
}