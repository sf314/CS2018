// Test the nichrome circuit using simple commands
// Also has automated testing sequence. Use #define to control test type

#define N_TEST_AUTOMATED

#include "CSNichrome.h"
CSNichrome nichrome;

void setup() {
    Serial.begin(9600);
    nichrome = CSNichrome(2);
    Serial.println("Nichrome test on pin " + String(nichrome.pin));
}

void loop() {
    if (Serial.available()) {
        char c = Serial.read();
        switch (c) {
            case 'a':
                nichrome.start();
                Serial.println("Start!");
                break;
            case 'z':
                nichrome.stop();
                Serial.println("Stop!");
                break;
            default:
                Serial.println("Invalid command!");
        }
    }
}