// CSVolt Class Header
// Stephen Flores
/* Notes:
* 
*/

#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class CSVolt {
public:
    CSVolt();   // Constructor
    
    // Object Configuration
    void config(int p);            // Configuration
    void setPin(int newPin);            // Change pin (called by config)
    void setSampleSize(int samples);    // Set number of samples to average
    
    // Data Acquisition
    float read();
    
    void setDebugMode(bool newDebug);
    
private:
    int pin;
    bool debugMode;
    int sampleSize;
    
    void debug(String str);
    void debugln(String str);
};