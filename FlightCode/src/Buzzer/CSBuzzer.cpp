// CSBuzzer implementation file
// Stephen Flores

#include "CSBuzzer.h"

// Initialization
CSBuzzer::CSBuzzer() {
    shouldDebug = false;
    pin = 0;
    isOn = false;
    
    songMode = false;
    songStartTime = 0;
    songCurrentTime = 0;
}

// Configuration
void CSBuzzer::config(int p) {
    pin = p;
    pinMode(p, OUTPUT);
    // pinMode(p + 1, OUTPUT);
    digitalWrite(pin, LOW);
    // digitalWrite(pin + 1, LOW);
    isOn = false;
    songMode = false;
    debugln("CSBuzzer: configured on pin " + String(p));
}

void CSBuzzer::setDebugMode(bool b) {
    shouldDebug = b;
}

void CSBuzzer::debugln(String s) {
    if (shouldDebug) {
        Serial.println(s);
    }
}

void CSBuzzer::debug(String s) {
    if (shouldDebug) {
        Serial.print(s);
    }
}

void CSBuzzer::activate() {
    isOn = true;
    debugln("CSBuzzer: activated");
}

void CSBuzzer::deactivate() {
    isOn = false;
    debugln("CSBuzzer: deactivated");
}

void CSBuzzer::toggle() {
    isOn = !isOn;
    debugln("CSBuzzer: toggled to state " + String(isOn));
}

void CSBuzzer::playSong() {
    songMode = !songMode;
    debugln("CSBuzzer: songMode set to " + String(songMode));
    if (songMode) {
        // set start time for song
        songStartTime = millis();
    } else {
        deactivate();
    }
}

void CSBuzzer::main() {
    // Guard songMode
    if (songMode) {
        // Run song process
        sing();
        return; // exit early
    }
    
    if (isOn) {
        //digitalWrite(pin, HIGH);
        //tone(pin, 700);
        
        digitalWrite(pin, HIGH);
        // digitalWrite(pin + 1, LOW);
    } else {
        //digitalWrite(pin, LOW);
        //tone(pin, 700);
        
        digitalWrite(pin, LOW);
        // digitalWrite(pin + 1, LOW);
    }
    
}

void CSBuzzer::sing() {
    songCurrentTime = millis() - songStartTime;
    // Oh dear
    // queue?
    // Remove from queue when deltaT exceeds node time
}

void CSBuzzer::playStartup() {
    tone(pin, 523);
    delay(300);
    tone(pin, 659);
    delay(300);
    tone(pin, 784);
    delay(300);
    tone(pin, 1046);
    delay(300);
    noTone(pin);
}