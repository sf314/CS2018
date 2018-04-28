// Test the GPS Module

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Adafruit_GPS.h"

#include "CSGps.h"

// Things that shall exist in the global scope:
SoftwareSerial gpsss(7, 8); // Rx, Tx (MISO, MOSI)
// Adafruit_GPS agps(&gpsss);
CSGps gps(&gpsss);

void setup() {
    Serial.begin(9600);
    // gps.begin(9600);
    
    gps.config();
    gps.shouldDebug = true;
    delay(1000);
    Serial.println("GPS start");
}

long currentTime = 0;
long previousTime = 0;

void loop() {
    // // Keep track of time constantly
    currentTime = millis();
    
    // // Update GPS constantly
    gps.update();
    
    // Periodically print data
    if (currentTime - previousTime >= 1000) {
        // Pretend main code here
        Serial.println("Main!");
        
        // Do things for other subsystems
        // ...
        
        // Print GPS status stuff
        Serial.println(gps.time);
        Serial.println(gps.altitude);
        previousTime = currentTime;
    }

    // if (gpsss.available()) {
    //     while (gpsss.available()) {
    //         char c = gpsss.read();
    //         Serial.print(c);
    //     }
    // }
    
}
