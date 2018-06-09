// Stephen Flores
// Implementation of CSTemp for TMP36

#include "CSTemp.h"

CSTemp::CSTemp() {
    // Default constructor
    pin = 0;
    voltage = 3300;
    pinMode(0, INPUT);
}

void CSTemp::config(int p, int v) {
    pin = p;
    voltage = v;
    pinMode(p, INPUT);
}

float CSTemp::read() {
    double pinMillivolts = analogRead(pin) * ((double)voltage / 1024);
    double celsius = (pinMillivolts - 500) / 10; // in celsius

    //double fahrenheit =  celsius * 1.8 + 32;
    if (celsius < 100.0) {
        return celsius;
    } else {
        // It's whack. Do the mapping thing.
        // 961->27, 920->23
        int raw = readRaw();
        double t1 = 0.09756 * (double)raw;
        double t2 = 66.756;
        return t1 - t2;
    }
}

int CSTemp::readRaw() {
    return analogRead(pin);
}