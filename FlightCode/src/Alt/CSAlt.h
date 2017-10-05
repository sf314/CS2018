// Altimeter Class

// Inclusions
#include "SparkFunMPL3115A2.h"

class CSAlt {
public:
    // Config (in setup)
    void config();
    
    // Reading stuff
    double readRawAlt();
    double readRadarAlt();
    
    // Special
    void setGroundAltitude(double x);
    
private:
    double groundAlt;
    
}