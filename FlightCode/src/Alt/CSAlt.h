// Altimeter Class

// Inclusions
#include "SparkFunMPL3115A2.h"

class CSAlt {
public:
    // Constructor
    CSAlt();
    
    // Config (in setup)
    void config();
    
    // Reading stuff
    double readRaw();
    double readRadar();
    
    // Special
    void setGroundAltitude(double x);
    
private:
    double groundAlt;
    MPL3115A2 hardware;
    
};