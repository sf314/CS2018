/*
ASU CanSat Flight Software
*/


// *** Inclusions
#include "src/Alt/CSAlt.h"
#include "src/Temp/CSTemp.h"
#include "src/GPS/CSGps.h"

// *** Objects
CSAlt alt;
CSTemp temp;
CSGps gps;

// *** Setup


void setup() {
    Serial.begin(9600);
    Wire.begin();
    
    alt.config();
    temp.config(14, 3300);
    gps.config();
}




void loop() {
    delay(100);
}

