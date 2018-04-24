


#include "CSVolt.h"

CSVolt volt;

void setup() {
    Serial.begin(9600);
    volt.config(15);
    volt.setDebugMode(true);
    
    // pinMode(16, INPUT);
    // analogReference(DEFAULT);
    // analogReadResolution(12);
}

void loop() {
    // float r = volt.read();
    // Serial.println("Read: " + String(r));
    
    // int r = analogRead(16);
    // double v = analogToVolts(r);
    // Serial.println(String(r) + " => " + String(v));
    
    // int r = analogRead(16);
    // float volt = r / 4095.0 * 3.3;
    // float volt2 = (volt * 32.0 / 10);// - 0.32; // * 3.2?
    // Serial.println(String(volt) + "," + String(volt2));

    Serial.println(volt.read());
    
    delay(500);
}


/*
Want, Got
5.24, 5.57
5.50, 5.82
5.05, 5.37

Off by 0.325!
*/