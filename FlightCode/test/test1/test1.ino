// Testing multiple sensors

// Libs:
#include <Arduino.h>
#include <Wire.h>

// Objs:



void setup() {
    Serial.println(9600);
}

long currentTime = 0;
long previousTime = 0;

void loop() {
    // Update time
    currentTime = millis();
    
    // Main loop
    if (currentTime - previousTime >= 1000) {
        
        
        previousTime = currentTime;
    }
}