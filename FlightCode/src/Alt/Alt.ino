// Testing the CSAlt library

#include <Wire.h>
#include "CSAlt.h"

int i = 0;
CSAlt altimeter;

void setup() {
    Serial.begin(9600);
    Serial.println("Starting up!");
    altimeter.init();
    altimeter.setGroundHeight(altimeter.alt());
}

void loop() {
    Serial.print("Alt: ");
    Serial.println(altimeter.altRadar());
    delay(250);
}