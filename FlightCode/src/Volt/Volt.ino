


#include "CSVolt.h"

CSVolt volt;

void setup() {
    Serial.begin(9600);
    volt.config(22, 3.3);
    volt.setDebugMode(false);
}

void loop() {
    float r = volt.read();
    Serial.println("Read: " + String(r));
    
    delay(1000);
}
