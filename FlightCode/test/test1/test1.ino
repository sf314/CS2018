// Testing multiple sensors

// Libs:
#include <Arduino.h>
#include <Wire.h>

// Local libs??? No going back a directory?
// #include "CSTemp.h"
// #include "CSGps.h"
// #include "CSAlt.h"
#include "../../src/Temp/CSTemp.h"
#include "../../src/Alt/CSAlt.h"
#include "../../src/GPS/CSGps.h"

// Objs:
CSTemp temp;
CSGps gps;
CSAlt alt;


void setup() {
    Serial.println(9600);
    Wire.begin();
    
    temp.config(14, 3300);
    gps.config();
    gps.shouldDebug = true;
    alt.init();
    
    delay(1000);
    
}

long currentTime = 0;
long previousTime = 0;

void loop() {
    // Update time
    currentTime = millis();
    
    // Update GPS
    gps.update();
    
    // Main loop
    if (currentTime - previousTime >= 1000) {
        
        Serial.println("Temp = " + String(temp.read()));
        Serial.println("GPS lat = " + String(gps.lat));
        Serial.println("Alt = " + String(alt.alt()));
        
        Serial.println("\n\n");
        previousTime = currentTime;
    }
}