// Test the nichrome circuit using simple commands
// Also has automated testing sequence. Use #define to control test type

#define N_TEST_AUTOMATED

#include "CSNichrome.h"
#include <SoftwareSerial.h>
CSNichrome nichrome;
SoftwareSerial xbee(0, 1);

void setup() {
    Serial.begin(9600);
    xbee.begin(9600);
    pinMode(13, OUTPUT);
    nichrome = CSNichrome(2);
    Serial.println("Nichrome test on pin " + String(nichrome.pin));
}

// Time vars
long cTime = 0;
long pTime = 0;
bool ledOn = false;

void loop() {
    if (Serial.available()) {
        char c = Serial.read();
        switch (c) {
            case 'a':
                nichrome.start();
                xbee.println("Start!");
                Serial.println("Start!");
                for (int i = 0; i < 4; i++) {
                    delay(1000);
                    xbee.println(i);
                    Serial.println(i);
                }
                xbee.println("Stopping.");
                Serial.println("Stopping.");
                nichrome.stop();
                
                delay(4000);
                
                nichrome.start();
                xbee.println("Start!");
                Serial.println("Start!");
                for (int i = 0; i < 4; i++) {
                    delay(1000);
                    xbee.println(i);
                    Serial.println(i);
                }
                xbee.println("Stopping.");
                Serial.println("Stopping.");
                nichrome.stop();
                
                break;
            case 'z':
                nichrome.stop();
                xbee.println("Stop!");
                Serial.println("Stop!");
                break;
            default:
                xbee.println("Invalid command!");
                Serial.println("Invalid command!");
        }
    }
    
    if (xbee.available()) {
        char c = xbee.read();
        switch (c) {
            case 'a':
                nichrome.start();
                xbee.println("Start!");
                Serial.println("Start!");
                for (int i = 0; i < 4; i++) {
                    delay(1000);
                    xbee.println(i);
                    Serial.println(i);
                }
                xbee.println("Stopping.");
                Serial.println("Stopping.");
                nichrome.stop();
                
                delay(4000);
                
                nichrome.start();
                xbee.println("Start!");
                Serial.println("Start!");
                for (int i = 0; i < 4; i++) {
                    delay(1000);
                    xbee.println(i);
                    Serial.println(i);
                }
                xbee.println("Stopping.");
                Serial.println("Stopping.");
                nichrome.stop();
                
                break;
            case 'z':
                nichrome.stop();
                xbee.println("Stop!");
                Serial.println("Stop!");
                break;
            default:
                xbee.println("Invalid command!");
                Serial.println("Invalid command!");
        }
    }
    
    
    cTime = millis();
    if (cTime - pTime >= 500) {
        if (ledOn) {
            digitalWrite(13, LOW);
        } else {
            digitalWrite(13, HIGH);
        }
        pTime = cTime;
    }
}