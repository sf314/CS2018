// CSComms

// Use softwareSerial object for stuff

#include <Arduino.h>
#include <SoftwareSerial.h>


class CSComms {
public:
    // Init
    CSComms(SoftwareSerial* s);
    void config();
    
    // Passthrough stuff
    void print(String s);
    void println(String s);
    void begin(int x);
    bool available();
    char read();
    
private:
    SoftwareSerial* ss;
};