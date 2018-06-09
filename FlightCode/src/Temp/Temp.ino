

#include "CSTemp.h"

CSTemp temp;

void setup() {
    Serial.begin(9600);
    temp.config(14, 3300);
    
}

void loop() {
    Serial.println(temp.read());
    Serial.println(temp.readRaw());
    Serial.println(analogRead(14));
    delay(500);
}