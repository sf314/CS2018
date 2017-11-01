
#include "CSAlt.h"


CSAlt::CSAlt() {
    // Anything?
    Wire.begin();
}

void CSAlt::config() {
    hardware.begin();
    hardware.setModeAltimeter();
    hardware.setOversampleRate(7);
    hardware.enableEventFlags();
}

double CSAlt::readRaw() {
    double average = 0;
    
    for (int i = 0; i < 20; i++) {
        average += hardware.readAltitude();
        delay(10);
    }
    
    average /= 20.0;
    
    return average;
}

double CSAlt::readRadar() {
    return readRaw() - groundAlt;
}

void CSAlt::setGroundAltitude(double x) {
    groundAlt = x;
}

