// CSLog
// Save data to the SD
// Support regular telemetry, and logFiles

// Build your datastring externally, please. Then write in one go.

#include <Arduino.h>
#include <Wire.h>
#include <SD.h>

class CSLog {
public:
    CSLog();
    bool config(int p);
    // void setTelemFile(String s);
    // void setLogFile(String s);
    void setDebugMode(bool b);
    
    // Logging data
    bool write(String s); // Write to main telem
    bool log(String s); // Write to aux logfile
    void debug(String s);
private:
    bool debugMode;
    File dataFile;
    int pin;
    // String telemFile;
    // String logFile;
};