// Test the GPS Module


#include "CSGps.h"

//SoftwareSerial gps(0, 1); // 7 and 8
CSGps gps;

void setup() {
    //gps.begin(9600); // Don't use
    Serial.begin(9600);
    
}

long currentTime = 0;
long previousTime = 0;

void loop() {
    rawRead();
    
    if (currentTime - previousTime >= 1000) {
        // Pretend main code here
        Serial.println("Main!");
        
        // Do things for other subsystems
        
        // Check status of GPS
    }
    
    gps.update();
    // GPS data handling (main?)
    
}

void rawRead() {
    // if (gps.available()) {
    //     Serial.print("Got from GPS: ");
    //     while (gps.available()) {
    //         char c = gps.read();
    //         Serial.print(c);
    //     }
    //     Serial.println();
    // } else {
    //     Serial.println("Nothing!");
    // }
}