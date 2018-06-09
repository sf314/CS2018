// CSCamera.cpp
// Mini Spy Camera header

#include <Arduino.h>
#include "CSCamera.h"

CSCamera::CSCamera() {
    
}

void CSCamera::config(int p) {
    pin = p;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
}

void CSCamera::turnOn() {
    digitalWrite(pin, LOW);
    delay(3000);
    digitalWrite(pin, HIGH);
}

void CSCamera::turnOff() {
    digitalWrite(pin, LOW);
    delay(3000);
    digitalWrite(pin, HIGH);
}

void CSCamera::takePic() {
    digitalWrite(pin, LOW);
    delay(100);
    digitalWrite(pin, HIGH);
}