/*
ASU CanSat Flight Software
Stephen Flores

Confirmed operational:
CSTemp(pin: 14, volt: 3300)

The file structure will attempt to somewhat resemble CFS
*/

// *** Inclusions
#include <SoftwareSerial.h>
// #include "src/Comms/CSComms.h"
// #include "src/Temp/CSTemp.h"
#include "src/Alt/CSAlt.h"
#include "src/Log/CSLog.h"
#include "src/Gyro/CSGyro.h"

// *** Objects
// SoftwareSerial s(0, 1); // MOSI, MISO
// CSComms xbee(&s);
// CSTemp temp;
// SoftwareSerial gps(7,8);
CSAlt alt;
CSLog sd;
CSGyro gyro;

// *** Vars
long currentTime    = 0;
long previousTime   = 0;
String dataString   = "";

// *** State Vars
int state = 0;
    const int state_boot        = 0;
    const int state_launchpad   = 1;
    const int state_flight      = 2;
    const int state_deploy      = 3;
    const int state_descent     = 4;
    const int state_landed      = 5;

// *** Telemetry
float altitude;
float temperature;
GyroData_t gyroData;


// ********** Setup ***********************************************************
void setup() {
    Serial.begin(9600);
    Wire.begin();
    // xbee.begin(9600);
    // gps.begin(9600);
    alt.init();
    sd.config(1);
    
    // xbee.config();
    // temp.config(14, 3300);
    alt.setGroundHeight(alt.read());
    sd.log("Booted up");
}

// ********** Loop ************************************************************
void loop() {
    
    currentTime = millis();
    checkForCommands();
    
    if (currentTime - previousTime >= 1000) {
        Serial.println("\n\nMain");
        dataString = "";
        
        // Update telemetry
        altitude = alt.read();
        gyroData = gyro.getData();
        
        // Update telemetry string
        dataString += String(currentTime) + ",";
        dataString += String(altitude) + ","; 
        dataString += String(gyroData.x) + ",";
        dataString += String(gyroData.y) + ",";
        dataString += String(gyroData.z) + ",";
        
        // Switch on state
        switch (state) {
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
                sd.log("Invalid state: " + String(state));
        }
        

        Serial.println(dataString);
        sd.write(dataString);
        // xbee.println(dataString);
        
        previousTime = currentTime;
    }
    
    // ***** Parallel threads:

    // Update GPS
    // if (gps.available()) {
    // 	Serial.print((char)gps.read());
    // }
    
    // Update buzzer
    
}



// ********** Handle incoming communications **********************************
void checkForCommands() {
    // if (xbee.available()) {
    //     char c = xbee.read();
    //     switch (c) {
    //         case 'a':
    //             //buzzer.activate();
    //             break;
    //         case 's':
    //             //buzzer.deactivate();
    //             break;
    //         default:
    //             xbee.println("Invalid command");
    //     }
    // }
    
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





// ********** State Operations ************************************************
void boot_ops() {
    
}

void launchpad_ops() {
    
}

void flight_ops() {
    
}

void deploy_ops() {
    
}

void descent_ops() {
    
}

void landed_ops() {
    
}
