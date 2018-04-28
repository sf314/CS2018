/*
ASU CanSat Flight Software
Stephen Flores

Confirmed operational:
CSTemp(pin: 14, volt: 3300)

The file structure will attempt to somewhat resemble CFS
*/

// *** Inclusions
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include "MissionDefs.h"
#include "src/Telem/CSTelem.h"
#include "src/Comms/CSComms.h"
#include "src/Temp/CSTemp.h"
#include "src/Alt/CSAlt.h"
// #include "src/Log/CSLog.h"
#include "src/Gyro/CSGyro.h"
#include "src/GPS/CSGps.h"
#include "src/Nichrome/CSNichrome.h"

// *** Objects
SoftwareSerial xbee(0, 1); // MOSI, MISO
// CSComms xbee(&s);
CSTemp temp;
SoftwareSerial gpsss(7,8); CSGps gps(&gpsss);
CSAlt alt;
// CSLog sd;
CSGyro gyro;
CSTelem telem;
CSNichrome nichrome;

// *** Vars
long currentTime    = 0;
long previousTime   = 0;
String dataString   = "";

// *** State Vars
const int state_boot        = 0;
const int state_launchpad   = 1;
const int state_flight      = 2;
const int state_deploy      = 3;
const int state_descent     = 4;
const int state_landed      = 5;

// *** Telemetry
double vel = 0.0;
double prevAlt = 0.0;


// ********** Setup ***********************************************************
void setup() {
    Serial.begin(9600);
    xbee.begin(9600);
    Wire.begin();
    // xbee.begin(9600);
    // gps.begin(9600);
    alt.init();
    // sd.config(1);
    temp.config(14,3300);
    
    telem.teamID = 1234;
    // xbee.config();
    // temp.config(14, 3300);
    alt.setGroundHeight(alt.read()); // Danger!
    // sd.log("Booted up");
    telem.state = state_landed;
    
    gps.config();
    
    nichrome = CSNichrome(2);
}

// ********** Loop ************************************************************
void loop() {
    
    currentTime = millis();
    checkForCommands();
    
    if (currentTime - previousTime >= 1000) {
        Serial.println("\n\nMain");
        dataString = "";
        
        // Update telemetry
        
        telem.altitude = alt.read(); 
        telem.temp = temp.read();
        
        GyroData_t gyroData = gyro.getData();
        telem.gyro_x = gyroData.x;
        telem.gyro_y = gyroData.y;
        telem.gyro_z = gyroData.z;
        
        
        // Update telemetry string
        dataString = telem.asString();
        Serial.println(dataString);
        xbee.println(dataString);
        // sd.write(dataString);
        
        // Update velocity
        vel = telem.altitude - prevAlt;
        prevAlt = telem.altitude;
        
        // Switch on state
        switch (telem.state) {
            case state_boot:
                boot_ops();
                break;
            case state_launchpad:
                launchpad_ops();
                break;
            case state_flight:
                flight_ops();
                break;
            case state_deploy:
                deploy_ops();
                break;
            case state_descent:
                descent_ops();
                break;
            case state_landed:
                landed_ops();
                break;
            default:
                // sd.log("Invalid state: " + String(state));
                break;
        }
        
        previousTime = currentTime;
    }
    
    // ***** Parallel threads:

    // Update GPS
    gps.update();
    
    // Update buzzer
    
}



// ********** Handle incoming communications **********************************
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
            case 'x':
                for (int t = 0; t < 2; t++) {
                    xbee.println("Start cut " + String(t + 1));
                    nichrome.start();
                    for (int i = 0; i < 4; i++) {
                        delay(1000);
                    }
                    xbee.println("Stop cut " + String(t + 1));
                    nichrome.stop();
                    if (t == 0) {
                        delay(4000);
                    }
                }
                break;
            case 'g':
                alt.setGroundHeight(alt.read());
                break;
            default:
                xbee.println("Invalid command: " + String(c));
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
            case 'x':
                for (int t = 0; t < 2; t++) {
                    xbee.println("Start cut " + String(t + 1));
                    nichrome.start();
                    for (int i = 0; i < 4; i++) {
                        delay(1000);
                    }
                    xbee.println("Stop cut " + String(t + 1));
                    nichrome.stop();
                    if (t == 0) {
                        delay(4000);
                    }
                }
                break;
            default:
                Serial.println("Invalid command: " + String(c));
        }
    }
}





// ********** State Operations ************************************************
void boot_ops() {
    // On boot, check previous state and time from EEPROM
    // Make sure to recover state, met, and groundAlt
    Serial.println("Bootup. Starting in 5 seconds...");
    xbee.println("Bootup. Starting in 5 seconds...");
    delay(5000);
    telem.state = state_launchpad;
}

void launchpad_ops() {
    // Check for increase in altitude
    if (telem.altitude >= CS_MIN_FLIGHT_THRESH) {
        telem.state = state_flight;
    }
}

void flight_ops() {
    bool goingDown = (vel < -5.0);
    bool atAlt = (telem.altitude <= 310.0);
    if (goingDown && atAlt) {
        telem.state = state_deploy;
    }
}

void deploy_ops() {
    for (int t = 0; t < 2; t++) {
        xbee.println("Start cut " + String(t + 1));
        Serial.println("Start cut " + String(t + 1));
        nichrome.start();
        for (int i = 0; i < 4; i++) {
            delay(1000);
        }
        xbee.println("Stop cut " + String(t + 1));
        Serial.println("Stop cut " + String(t + 1));
        nichrome.stop();
        if (t == 0) {
            delay(4000);
        }
    }
    telem.state = state_descent;
}

void descent_ops() {
    if (telem.altitude < CS_MIN_FLIGHT_THRESH) {
        telem.state = state_landed;
    }
}

void landed_ops() {
    xbee.println("You are landed!");
    Serial.println("You are landed!");
}
