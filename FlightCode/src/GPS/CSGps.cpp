// Implementatin file

#ifndef CSGps_cpp
#define CSGps_cpp

#include "CSGps.h"

Dat::Dat() {
    satellites = 0;
    altitude = 0;
    fix = false;
    
    lat = 0;
    lon = 0;
    
    hours = 0, minute = 0, seconds = 0, year = 0, month = 0, day = 0;
    
}

CSGps::CSGps() {
    dat = Dat();
}

void CSGps::update() {
    
}

void CSGps::config() {
    //agps.begin(9600);
}

#endif