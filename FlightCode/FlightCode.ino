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

// *** Objects
SoftwareSerial xbee(0, 1); // MOSI, MISO
// CSComms xbee(&s);
CSTemp temp;
SoftwareSerial gps(7,8);
CSAlt alt;
// CSLog sd;
CSGyro gyro;
CSTelem telem;

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
    gps.begin(9600);
    Wire.begin();
    // xbee.begin(9600);
    // gps.begin(9600);
    alt.init();
    // sd.config(1);
    temp.config(14,3300);
    
    telem.teamID = 1234;
    // xbee.config();
    // temp.config(14, 3300);
    alt.setGroundHeight(alt.read());
    // sd.log("Booted up");
    telem.state = state_landed;
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
        // sd.write(dataString);
        Serial.println(dataString);
        
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
        
        xbee.println(dataString);
        
        previousTime = currentTime;
    }
    
    // ***** Parallel threads:

    // Update GPS
    if (gps.available()) {
    	Serial.print((char)gps.read());
    }
    
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
            default:
                Serial.println("Invalid command: " + String(c));
        }
    }
}





// ********** State Operations ************************************************
void boot_ops() {
    // On boot, check previous state and time from EEPROM
    // Make sure to recover state, met, and groundAlt
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
    
}

void descent_ops() {
    
}

void landed_ops() {
    Serial.println("Testing...");
}
