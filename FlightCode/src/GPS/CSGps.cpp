// Implementatin file

#ifndef CSGps_cpp
#define CSGps_cpp

#include "CSGps.h"


CSGps::CSGps(Adafruit_GPS* agps) {
    adaGpsPtr = agps;
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
    if (adaGpsPtr->newNMEAreceived()) {
        debugln("New NMEA sentence received");
        
        if (!adaGpsPtr->parse(adaGpsPtr->lastNMEA())) {
            debugln("Failed to parse sentence!");
        } else {
            // Data updated here
            debugln("Data fields updated");
            hour = adaGpsPtr->hour;
            minute = adaGpsPtr->minute;
            seconds = adaGpsPtr->seconds;
            
            year = adaGpsPtr->year;
            month = adaGpsPtr->month;
            day = adaGpsPtr->day;
            
            fix = adaGpsPtr->fix;
            lat = adaGpsPtr->latitudeDegrees;
            lon = adaGpsPtr->longitudeDegrees;
            altitude = adaGpsPtr->altitude;
        }
    } else {
        // debugln("No new packet");
    }
    
    // Raw printing of serial data
    if (shouldDebug) {
        // debugln("Raw:");
        char c = adaGpsPtr->read(); 
        Serial.print(c);
    }
    
}

void CSGps::config() {
    debugln("Configure");
    adaGpsPtr->begin(9600); // throws error?
    
    // Send commands for setting output
    adaGpsPtr->sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    adaGpsPtr->sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
    // adaGpsPtr->sendCommand(PGCMD_ANTENNA); // This one too?
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

bool CSGps::available() {
    return adaGpsPtr->gpsSwSerial->available();
}

char CSGps::read() {
    return adaGpsPtr->read();
}

#endif