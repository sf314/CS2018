// CSVolt Class Implementation
// Stephen Flores
/* Notes:
* 
*/

#include "CSVolt.h"
#include <string.h>

// Constructor
CSVolt::CSVolt() {
    // Set default values
    pin = 11;
    debugMode = false;
    sampleSize = 1;
}

// Configuration options
void CSVolt::config(int p) {
    pin = p;
    pinMode(p, INPUT);
    analogReference(DEFAULT);
    analogReadResolution(12);
}

// Specific configuration
void CSVolt::setPin(int newPin) {pin = newPin;}
void CSVolt::setSampleSize(int samples) {sampleSize = samples;}
void CSVolt::setDebugMode(bool newDebug) {debugMode = newDebug;}

// Enable verbose output
void CSVolt::debug(String str) {
    if (debugMode) {
        Serial.print(str);
    }
}

void CSVolt::debugln(String str) {
    if (debugMode) {
        Serial.println(str);
    }
}

// Reading voltage
float CSVolt::read() {
    debug("CSVolt.read(): ");
    float sum = 0;
    for (int index = 0; index < sampleSize; index++) {
        float x = analogRead(pin); // * 3.3 / 1024.0;
        sum += x;
        debug(String(x) + ", ");
        delay(10);
    }
    
    float average = sum / sampleSize;
    debugln("\n\tAverage: " + String(average));
    
    float volt = average / 4095.0 * 3.3;
    float volt2 = (volt * 32.0 / 10);// - 0.32; // * 3.2?
    float result = volt2 - 0.325;
    return result;
}