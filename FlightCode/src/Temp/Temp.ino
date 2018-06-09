

#include "CSTemp.h"

CSTemp temp;

void setup() {
    Serial.begin(9600);
    temp.config(14, 3300);
    
}

void loop() {
    Serial.println(temp.read());
    delay(500);
}