

#include "CSNichrome.h"

CSNichrome::CSNichrome(int p) {
    pin = p;
    pinMode(pin, OUTPUT);
}
CSNichrome::CSNichrome() {
    pin = 6;
}

void CSNichrome::start() {
    Serial.println("Starting burn...");
    digitalWrite(pin, HIGH);
}

void CSNichrome::stop() {
    Serial.println("Stopping burn...");
    digitalWrite(pin, LOW);
}