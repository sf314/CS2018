// CSGps header file
// Stephen Flores

#ifndef CSGps_h
#define CSGps_h

#include <Arduino.h>
#include <stdbool.h>
#include <stdint.h>
#include <SoftwareSerial.h>
#include "Adafruit_GPS.h"


class CSGps {
public:
    // CSGps(Adafruit_GPS* agps); // Init
    CSGps(SoftwareSerial* ss);
    void config();
    void update();
    void parsePacket();
    void debugln(String s);
    
    bool available();
    char read();
    
    // Meta
    int satellites;
    float altitude;
    bool fix;
    
    // Position: Degrees
    double lat;
    double lon;
    double time;
    
    // Time: 
    uint8_t hour, minute, seconds, year, month, day;
    
    bool shouldDebug;
    String temp;
    bool packetReceived;
private:
    // Adafruit_GPS* adaGpsPtr;
    SoftwareSerial* serial;
};



#endif