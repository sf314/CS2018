// CSVolt Class Header
// Stephen Flores
/* Notes:
* 
*/


class CSVolt {
public:
    CSVolt();   // Constructor
    
    // Object Configuration
    void config(int p, float v);            // Configuration
    void setPin(int newPin);            // Change pin (called by config)
    void setVoltage(float newVoltage);  // Set max voltage
    void setSampleSize(int samples);    // Set number of samples to average
    
    // Data Acquisition
    float read();
    
    void debugMode(bool newDebug);
    
private:
    int pin;
    float maxVoltage;
    bool debugMode;
    int sampleSize;
    
    void debug(String str);
};