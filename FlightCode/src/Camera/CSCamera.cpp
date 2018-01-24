// CSCamera.cpp
// Mini Spy Camera header

#include <Arduino.h>
#include "CSCamera.h"

CSCamera::CSCamera() {
    
}

void CSCamera::config(int p) {
    pin = p;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void CSCamera::turnOn() {
    digitalWrite(pin, HIGH);
    delay(500);
    digitalWrite(pin, LOW);
}

void CSCamera::turnOff() {
    digitalWrite(pin, HIGH);
    delay(500);
    digitalWrite(pin, LOW);
}

void CSCamera::takePic() {
    digitalWrite(pin, HIGH);
    delay(100);
    digitalWrite(pin, LOW);
}