/*
ASU CanSat Flight Software
Stephen Flores

Confirmed operational:
CSTemp(pin: 14, volt: 3300)

The file structure will attempt to somewhat resemble CFS
*/

// *** Inclusions
#include <Wire.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include "MissionDefs.h"
#include "src/Alt/CSAlt.h"
#include "src/Buzzer/CSBuzzer.h"
#include "src/Camera/CSCamera.h"
#include "src/CoreData/CSCoreData.h"
#include "src/Gyro/CSGyro.h"
#include "src/GPS/CSGps.h"
#include "src/Nichrome/CSNichrome.h"
#include "src/Telem/CSTelem.h"
#include "src/Temp/CSTemp.h"
#include "src/Volt/CSVolt.h"

// *** Serial objects
SoftwareSerial xbee(0, 1); // MOSI, MISO
SoftwareSerial gpsss(7,8); CSGps gps(&gpsss);

// *** Hardware objects
CSAlt alt;
CSBuzzer buzzer;
CSCamera cam;
CSCoreData coreData;
CSGyro gyro;
GyroData_t gData;
CSNichrome nichrome;
CSTemp temp;
CSVolt volt_A;
CSVolt volt_B;

// *** Vars
long currentTime    = 0;
long previousTime   = 0;
String dataString   = "";

// *** State declarations
const int state_boot        = 0;
const int state_launchpad   = 1;
const int state_flight      = 2;
const int state_deploy      = 3;
const int state_descent     = 4;
const int state_landed      = 5;

// *** Telemetry
CSTelem telem;
double vel = 0.0; // deltaAlt
double prevAlt = 0.0; 


// ********** Setup ***********************************************************
void setup() {
    // Init serial connections
    Serial.begin(9600);
    Wire.begin();
    xbee.begin(9600);
    gps.begin(9600);
    
    // Init hardware
    alt.init();
    buzzer.config(17);
    cam.config(5);
    coreData.config();
    gyro.config();
    nichrome.config(2);
    telem.teamID = 5324;
    telem.state = state_boot;
    temp.config(14,3300);
    volt_A.config(15);
    volt_A.config(16);
    
    coreData.writeInt("teamID", 5278);
    
    boot_ops(); // Recovery
}

// ********** Loop ************************************************************
void loop() {
    
    currentTime = millis();
    checkForCommands();
    
    if (currentTime - previousTime >= 1000) {
        
        // Serial.println("\n\nMain");
        dataString = "";
        
        // Update telemetry
            telem.altitude = alt.altRadar();
            telem.pressure = alt.press();
            
            GyroData_t gyroData = gyro.getData();
            telem.gyro_x = gyroData.x;
            telem.gyro_y = gyroData.y;
            telem.gyro_z = gyroData.z;
            
            telem.gps_time = gps.time;
            telem.gps_lat = gps.lat;
            telem.gps_lon = gps.lon;
            telem.gps_alt = gps.altitude;
            telem.gps_sats = gps.satellites;
            
            telem.temp = temp.read();
            telem.volt_A = volt_A.read();
            telem.volt_B = volt_B.read();
            
            telem.met++;
            telem.packetCount++;
        
        // Update velocity
            vel = telem.altitude - prevAlt;
            prevAlt = telem.altitude;
        
        // TEST: Temp
        
        // Switch on state
        switch (telem.state) {
            case state_boot:
                boot_ops(); // Recovery
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
                Serial.print("");
                break;
        }
        
        // Update telemetry string
            dataString = telem.asString();
            Serial.println(dataString);
            xbee.println(dataString);
        
        // Update core data
            coreData.writeLong(CS_CD_KEY_met, telem.met);
            coreData.writeLong(CS_CD_KEY_pCount, telem.packetCount);
            coreData.writeInt(CS_CD_KEY_state, telem.state);
            coreData.writeFloat(CS_CD_KEY_groundHeight, alt.groundHeight);
        
        previousTime = currentTime;
    }
    
    // ***** Parallel threads:

    // Update GPS
    gps.update();
    
    // Update buzzer
    buzzer.main();
}



// ********** Handle incoming communications **********************************
void checkForCommands() {
    if (xbee.available()) {
        performCommand(xbee.read());
    }
    
    if (Serial.available()) {
        performCommand(Serial.read());
    }
}

void performCommand(char c) {
    switch (c) {
        case 'b':
            buzzer.toggle();
            break;
        case 'x':
            Serial.println("LOG: Manual cut activated");
            xbee.println("LOG: Manual cut activated");
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
            coreData.writeFloat(CS_CD_KEY_groundHeight, alt.groundHeight);
            Serial.println("LOG: Ground height was set to " + String(alt.groundHeight));
            xbee.println("LOG: Ground height was set to " + String(alt.groundHeight));
            break;
        case 'r':
            telem.met = 0;
            telem.packetCount = 0;
            telem.state = 0;
            coreData.writeLong(CS_CD_KEY_met, telem.met);
            coreData.writeLong(CS_CD_KEY_pCount, telem.packetCount);
            coreData.writeInt(CS_CD_KEY_state, telem.state);
            break;
        case '0':
            telem.state = state_boot; break;
        case '1':
            telem.state = state_launchpad; break;
        case '2':
            telem.state = state_flight; break;
        case '3':
            telem.state = state_deploy; break;
        case '4':
            telem.state = state_descent; break;
        case '5':
            telem.state = state_landed; break;
        case 'c':
            cam.turnOff(); // Turns off the camera manually
        default:
            Serial.println("Invalid command: " + String(c));
    }
}





// ********** State Operations ************************************************
void boot_ops() {
    // On boot, check previous state and time from EEPROM
    // Make sure to recover state, met, and groundAlt
    Serial.println("Bootup. Starting in 5 seconds...");
    xbee.println("Bootup. Starting in 5 seconds...");
    delay(5000);
    // Recover state, met, packet count, and groundAlt
    float rec_groundHeight = coreData.readFloat(CS_CD_KEY_groundHeight);
    alt.setGroundHeight(rec_groundHeight);
    
    telem.state = coreData.readInt(CS_CD_KEY_state);
    telem.packetCount = coreData.readInt(CS_CD_KEY_pCount);
    telem.met = coreData.readInt(CS_CD_KEY_met);
    
    vel = 0.0;
    prevAlt = alt.altRadar(); // Close
    
    telem.teamID = coreData.readInt("teamID");
    // telem.state = state_landed;
}

void launchpad_ops() {
    // Check for increase in altitude
    if (telem.altitude >= CS_MIN_FLIGHT_THRESH) {
        telem.state = state_flight;
        xbee.println("LOG: Launching!");
        Serial.println("LOG: Launching!");
    }
}

void flight_ops() {
    bool goingDown = (vel < CS_DESCENT_VEL_THRESH);
    bool atAlt = (telem.altitude <= CS_DEPLOY_ALT);
    if (goingDown && atAlt) {
        xbee.println("LOG: Deploying!");
        Serial.println("LOG: Deploying!");
        telem.state = state_deploy;
    }
}

void deploy_ops() {
    // Perform cut
    nichrome.start();
    delay(CS_CUTTIME);
    nichrome.stop();
    
    // Start the camera
    cam.turnOn();
    telem.state = state_descent;
}

void descent_ops() {
    if (telem.altitude < CS_MAX_LANDED_ALT_THRESH) {
        telem.state = state_landed;
        cam.turnOff();
        xbee.println("LOG: You are landed!");
        Serial.println("LOG: You are landed!");
    }
}

void landed_ops() {
    buzzer.activate();
}
