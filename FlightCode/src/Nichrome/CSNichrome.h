// CSNichrome
// Run nichrome in a separate process (in state). Timer will not block.

#ifndef _csnichrome_h
#define _csnichrome_h

#include <Arduino.h>

class CSNichrome {
public:
    CSNichrome(int p);
    CSNichrome();
    
    void config(int p);
    
    void start();
    void stop();
    
    int pin;
private:
};


#endif