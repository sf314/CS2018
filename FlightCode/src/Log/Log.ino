// Saving to SD card

#include <Wire.h>
#include <SD.h>
#include "CSLog.h"

// SD Stuff
CSLog sd;
int sdPin = 10;

void setup() {
    Serial.begin(9600);
    
    sd.config(sdPin);
}

void loop() {
    
    sd.write(String(millis()));
    sd.log("All good");
    
    delay(1000);
}