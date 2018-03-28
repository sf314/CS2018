/*
ASU CanSat Flight Software
Stephen Flores

Confirmed operational:
CSTemp(pin: 14, volt: 3300)

*/

// *** Inclusions
#include <SoftwareSerial.h>
#include "src/Comms/CSComms.h"
#include "src/Temp/CSTemp.h"
#include "src/Alt/CSAlt.h"

// *** Objects
SoftwareSerial s(0, 1); // MOSI, MISO
CSComms xbee(&s);
CSTemp temp;
CSAlt alt;
SoftwareSerial gps(7,8);

// *** Vars
long currentTime = 0;
long previousTime = 0;
String dataString = "";


// *** Setup
void setup() {
    Serial.begin(9600);
    xbee.begin(9600);
    gps.begin(9600);
    alt.init();

    xbee.config();
    temp.config(14, 3300);
    alt.setGroundHeight(alt.alt());
}

// *** Loop
void loop() {
    
    currentTime = millis();
    checkForCommands();
    
    if (currentTime - previousTime >= 1000) {
        Serial.println("\n\nMain");
        dataString = "";

        dataString += String(currentTime) + ",";
        dataString += String(temp.read()) + ",";
        dataString += String(alt.alt()) + ","; 

        Serial.println(dataString);
        xbee.println(dataString);
        
        previousTime = currentTime;
    }

    // Check gps
    if (gps.available()) {
    	Serial.print((char)gps.read());
    }
    
}

void checkForCommands() {
    if (xbee.available()) {
        char c = xbee.read();
        switch (c) {
            case 'a':
                //buzzer.activate();
                break;
            case 's':
                //buzzer.deactivate();
                break;
            default:
                xbee.println("Invalid command");
        }
    }
    
    if (Serial.available()) {
        char c = Serial.read();
        switch (c) {
            case 'a':
                //buzzer.activate();
                break;
            case 's':
                //buzzer.deactivate();
                break;
            default:
                Serial.println("Invalid command");
        }
    }
}