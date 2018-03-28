//

#include "CSNichrome.h"
CSNichrome nichrome;

void setup() {
    Serial.begin(9600);
    nichrome = CSNichrome(23);
}

void loop() {
    Serial.println("Burining in 3s...");
    delay(3000);
    
    Serial.print("Burn on pin ");
    Serial.println(nichrome.pin);
    nichrome.start();
    
    delay(5000);
    
    Serial.println("Stop!");
    nichrome.stop();
    
    delay(5000);
}