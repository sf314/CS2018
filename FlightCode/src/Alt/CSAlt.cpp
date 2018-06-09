// Stephen Flores
// Implementation and whatnot

#include "CSAlt.h"

Intersema::BaroPressure_MS5607B private_baro(true);

void CSAlt::setGroundHeight(float gh) {
    groundHeight = gh;
}

void CSAlt::init() {
    private_baro.init();
}

float CSAlt::read() {
    int altCM = private_baro.getHeightCentiMeters(); // centimeters
    return ((float)altCM) / 100.0; // meters
}

float CSAlt::altRadar() {
    float currentAlt = read();
    return currentAlt - groundHeight;
}

float CSAlt::press() {
    return private_baro.internal_press;
}