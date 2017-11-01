// Test the GPS Module

#include <SoftwareSerial.h>

SoftwareSerial gps(7, 8); // Don't use

void setup() {
    gps.begin(9600); // Don't use
    Serial.begin(9600);
    
}

long currentTime = 0;
long previousTime = 0;

void loop() {
    //rawRead();
    
    if (currentTime - previousTime >= 1000) {
        // Pretend main code here
        Serial.println("Main!");
        
        // Do things for other subsystems
        
        // Check status of GPS
    }
    
    // GPS data handling (main?)
    
}

void rawRead() {
    if (gps.available()) {
        Serial.print("Got from GPS: ");
        while (gps.available()) {
            char c = gps.read();
            Serial.print(c);
        }
        Serial.println();
    } else {
        Serial.println("Nothing!");
    }
}