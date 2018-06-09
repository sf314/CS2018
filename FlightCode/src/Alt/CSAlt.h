// Stephen Flores
// Implementing CSAlt code
// Barometer class
// Has access to pressure, temperature, and altitude
// Uses proprietary library (really big)

#ifndef _CSAlt
#define _CSAlt
#include "IntersemaBaro.h"

class CSAlt {
public:
    void init();
    float read(); // Metres
    float altRadar(); // Metres from ground height
    float press(); // Pascals
    void setGroundHeight(float gh);
    float groundHeight = 0;
private:
};

#endif
