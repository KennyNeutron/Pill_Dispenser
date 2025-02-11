#include <HardwareSerial.h>
#include <Arduino.h>

HardwareSerial sim900(1);
#define PWRKEY 4

// Global variable for phone number with a default value
String phoneNumber = "+639xxxxxxxxx";  // Set default recipient number

void power_on_sim900() {
    pinMode(PWRKEY, OUTPUT);
    digitalWrite(PWRKEY, LOW);
    delay(1000); // Hold PWRKEY low for 1 second
    digitalWrite(PWRKEY, HIGH);
    delay(5000); // Wait for initialization
}

// Function to send SMS dynamically
void sendSMS(String message) {
    Serial.println("[DEBUG] Sending SMS to " + phoneNumber);
    
    sim900.println("AT+CMGF=1"); // Set SMS to text mode
    delay(1000);
    
    sim900.println("AT+CMGS=\"" + phoneNumber + "\""); // Use global phone number
    delay(1000);
    
    sim900.print(message); // Send message
    delay(1000);
    
    sim900.write(26); // CTRL+Z to send SMS
    delay(5000);
    
    Serial.println("[DEBUG] SMS Sent!");
}

void setup() {
    Serial.begin(115200);
    Serial.println("[DEBUG] Initializing SIM900A...");
    
    sim900.begin(9600, SERIAL_8N1, 16, 17); // RX, TX
    power_on_sim900();

    // Test AT command
    sim900.println("AT");
    delay(1000);
    while (sim900.available()) {
        Serial.write(sim900.read());
    }

    // Send SMS using global phone number
    sendSMS("Hello from ESP32 & SIM900A!");
}

void loop() {
    // You can call sendSMS() inside loop() whenever needed
}
