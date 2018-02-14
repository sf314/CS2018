// CSGps header file
// Stephen Flores

#ifndef CSGps_h
#define CSGps_h

#include <stdbool.h>
#include <stdint.h>
#include <SoftwareSerial.h>
#include "Adafruit_GPS.h"

// Had to put software serial and adafruit stuff in the .ccp file

class CSGps {
public:
    CSGps(Adafruit_GPS* agps); // Init
    void config();
    void update();
    void debugln(String s);
    void printAll();
    
    bool available();
    char read();
    
    // Meta
    int satellites;
    float altitude;
    bool fix;
    
    // Position: Degrees
    float lat;
    float lon;
    
    // Time: 
    uint8_t hour, minute, seconds, year, month, day;
    
    bool shouldDebug;
private:
    Adafruit_GPS* adaGpsPtr;
};



#endif