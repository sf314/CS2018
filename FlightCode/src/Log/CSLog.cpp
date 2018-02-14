// Implementation

#include "CSLog.h"


CSLog::CSLog() {
    pin = 0;
    // const char* tBuf = "telemetry.csv";
    // const char* lBuf = "log.csv";
    // memcpy(telemFile, tBuf, sizeof(tBuf));
    // memcpy(logFile, lBuf, sizeof(lBuf));
}

void CSLog::setDebugMode(bool b) {debugMode = b;};
// void CSLog::setLogFile(String s) {
//     char charBuf[50];
//     logFile = s.toCharArray(charBuf, 50);
// }
// void CSLog::setTelemFile(String s) {
//     char charBuf[50];
//     telemFile = s.toCharArray(charBuf, 50);
// }

void CSLog::debug(String s) {
    if (debugMode) {
        Serial.println(s);
    }
}

bool CSLog::config(int p) {
    pin = p;
    
    // Check SD
    if (!SD.begin(pin)) {
        debug("Could not intialize SD!");
        return false;
    } else {
        debug("Initialized SD");
        return true;
    }
}


bool CSLog::write(String s) {
    dataFile = SD.open("telem.csv", FILE_WRITE);
    if (dataFile) {
        dataFile.println(s);
        dataFile.close();
        return true;
    } else {
        debug("Could no open telem file");
        return false;
    }
}

bool CSLog::log(String s) {
    dataFile = SD.open("log.csv", FILE_WRITE);
    if (dataFile) {
        dataFile.println(s);
        dataFile.close();
        return true;
    } else {
        debug("Could no open log file");
        return false;
    }
}