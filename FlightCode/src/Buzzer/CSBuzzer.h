// CSBuzzer header file
// Stephen Flores

#ifndef _CSBuzzer_h
#define _CSBuzzer_h

#include <Arduino.h>


class CSBuzzer {
public:
    // initialization
    CSBuzzer();
    void config(int p);
    void setDebugMode(bool b);
    
    // main
    void main();
    
    // toggle mode
    void activate(); // Takes effect in main();
    void deactivate();
    void toggle();
    void playSong(); // time-dependent, run like main
    void playStartup(); // Note: uses delays. Takes 1 sec.
    
    // Two-wire interface
private:
    bool shouldDebug;
    bool isOn;
    
    int pin;
    void debugln(String s);
    void debug(String s);
    
    bool songMode;
    long songStartTime;
    long songCurrentTime;
    void sing();
};

#endif