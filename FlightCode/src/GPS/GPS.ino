// Test the GPS Module

#include <SoftwareSerial.h>

SoftwareSerial gps(7, 8);

void setup() {
    gps.begin(9600);
    Serial.begin(9600);
    
}


void loop() {
    // if (gps.available()) {
    //     Serial.print("Got from GPS: ");
    //     while (gps.available()) {
    //         char c = gps.read();
    //         Serial.print(c);
    //     }
    //     Serial.println();
    // } else {
    //     //Serial.println("Nothing!");
    // }
    
    
}