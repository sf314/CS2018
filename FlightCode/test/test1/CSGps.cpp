// Implementatin file

#ifndef CSGps_cpp
#define CSGps_cpp

#include "CSGps.h"

// This stuff has to go here for reasons.
SoftwareSerial gpsss(7, 8); // Rx, Tx (MISO, MOSI)
Adafruit_GPS agps(&gpsss);

CSGps::CSGps() {
    satellites = 0;
    altitude = 0;
    fix = false;
    
    lat = 0;
    lon = 0;
    
    hour = 0, minute = 0, seconds = 0, year = 0, month = 0, day = 0;
    
    shouldDebug = false;
}

void CSGps::update() {
    // Call this as often as possible!
    if (agps.newNMEAreceived()) {
        debugln("New NMEA sentence received");
        
        if (!agps.parse(agps.lastNMEA())) {
            debugln("Failed to parse sentence!");
        } else {
            // Data updated here
            debugln("Data fields updated");
            hour = agps.hour;
            minute = agps.minute;
            seconds = agps.seconds;
            
            year = agps.year;
            month = agps.month;
            day = agps.day;
            
            fix = agps.fix;
            lat = agps.latitudeDegrees;
            lon = agps.longitudeDegrees;
            altitude = agps.altitude;
        }
    }
}

void CSGps::config() {
    debugln("Configure");
    agps.begin(9600); // throws error?
    
    // Send commands for setting output
    agps.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    agps.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
    // agps.sendCommand(PGCMD_ANTENNA); // This one too?
}

void CSGps::debugln(String s) {
    // If debug, print string to Serial
    if (shouldDebug) {
        Serial.println("CSGps: " + s);
    }
}

void CSGps::printAll() {
    Serial.println("CSGps: Some current data fields:");
    Serial.print("\tFix: "); Serial.println(fix);
    Serial.print("\tSats: "); Serial.println(satellites);
    Serial.print("\tAlt: "); Serial.println(altitude);
    Serial.print("\tLat: "); Serial.println(lat);
    Serial.print("\tLon: "); Serial.println(lon);
    Serial.print("\tSec: "); Serial.println(seconds);
    Serial.println("\n\n");
}

#endif