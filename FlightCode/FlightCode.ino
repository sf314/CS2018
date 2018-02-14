/*
ASU CanSat Flight Software
*/


// *** Inclusions
#include <SoftwareSerial.h>
#include "src/Comms/CSComms.h"
#include "src/Buzzer/CSBuzzer.h"
#include "src/GPS/CSGps.h"

// *** Objects
SoftwareSerial s(0, 1); // MOSI, MISO
CSComms xbee(&s);

SoftwareSerial gpsss(7, 8); // Rx, Tx (MISO, MOSI)
Adafruit_GPS agps(&gpsss);
CSGps gps(&agps);

CSBuzzer buzzer;

// *** Setup


void setup() {
    Serial.begin(9600);
    s.begin(9600);
    
    xbee.config();
    buzzer.config(20);
    
    xbee.begin(9600);
    gps.config();
    gps.shouldDebug = true;
    buzzer.setDebugMode(true);
    
}


long currentTime = 0;
long previousTime = 0;

void loop() {
    
    // GPS Test loop (using raw s);
    while (1) {
        if (s.available()) {
            //Serial.println("Received char!");
            char c = s.read();
            Serial.print(c);
        } else {
            
        }
        
        if (Serial.available()) {
            while (1) {};
        }
        
        delay(0);
    }
    
    currentTime = millis();
    checkForCommands();
    
    if (currentTime - previousTime >= 1000) {
        Serial.println("\n\nMain");
        gps.printAll();
        
        previousTime = currentTime;
    }
    
    // Constant proc
    gps.update();
    buzzer.main();
}

void checkForCommands() {
    if (xbee.available()) {
        char c = xbee.read();
        switch (c) {
            case 'a':
                buzzer.activate();
                break;
            case 's':
                buzzer.deactivate();
                break;
            default:
                xbee.println("Invalid command");
        }
    }
    
    if (Serial.available()) {
        char c = Serial.read();
        switch (c) {
            case 'a':
                buzzer.activate();
                break;
            case 's':
                buzzer.deactivate();
                break;
            default:
                Serial.println("Invalid command");
        }
    }
}