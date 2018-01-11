// CSCamera.h
// Mini Spy Camera header

#include <Arduino.h>

class CSCamera {
public:
    // init
    CSCamera();
    
    // Config
    void config(int p);
    
    // Funcs
    void turnOn();
    void turnOff();
    void takePic();
    
private:
    int pin;
};