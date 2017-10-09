// CSVolt Class Implementation
// Stephen Flores
/* Notes:
* 
*/

// Constructor
CSVolt::CSVolt() {
    // Set default values
    pin = 11;
    debugMode = false;
    sampleSize = 1;
}

// Configuration options
void CSVolt::config(int p, float v) {
    pin = p;
    maxVoltage = v;
}

// Specific configuration
void CSVolt::setPin(int newPin) {pin = newPin;}
void CSVolt::setVoltage(int newVoltage) {maxVoltage = newVoltage;}
void CSVolt::setSampleSize(int samples) {sampleSize = samples;}
void CSVolt::debugMode(bool newDebug) {debugMode = newDebug;}

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
    debug("CSVolt.read(): ")
    float sum = 0;
    for (int index = 0; index < sampleSize; index++) {
        float x = analogRead(pin); // * 3.3 / 1024.0;
        sum += x;
        debug(String(x) + ", ")
        delay(10);
    }
    
    float average = sum / 10.0;
    debugln("\n\tAverage: " + String(average));
    return average;
}