// Test the GPS Module

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Adafruit_GPS.h"

#include "CSGps.h"

// Things that shall exist in the global scope:
CSGps gps;

void setup() {
    Serial.begin(9600);
    
    gps.config();
    delay(1000);
}

long currentTime = 0;
long previousTime = 0;

void loop() {
    // Keep track of time constantly
    currentTime = millis();
    
    // Update GPS constantly
    gps.update();
    
    // Periodically print data
    if (currentTime - previousTime >= 1000) {
        // Pretend main code here
        Serial.println("Main!");
        
        // Do things for other subsystems
        // ...
        
        // Print GPS status stuff
        gps.printAll();
        previousTime = currentTime;
    }
    
}
