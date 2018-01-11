// CSGps header file
// Stephen Flores

#ifndef CSGps_h
#define CSGps_h

#include <stdbool.h>
#include <stdint.h>
#include <SoftwareSerial.h>
#include "Adafruit_GPS.h"


// Things that shall exist in the global scope:
SoftwareSerial ss(0, 1);
Adafruit_GPS agps(&ss);

class Dat {
public:
    Dat();
    
    // Meta
    int satellites;
    float altitude;
    boolean fix;
    
    // Position: Degrees
    float lat;
    float lon;
    
    // Time: 
    uint8_t hours, minute, seconds, year, month, day;
    
private:
};

class CSGps {
public:
    CSGps(); // Init
    void config();
    void update();
    
    Dat dat;
private:
};



#endif