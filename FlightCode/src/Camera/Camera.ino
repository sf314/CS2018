// Stephen Flores
// Test driver for camera

#include <Arduino.h>
#include "CSCamera.h"

CSCamera cam;

void setup() {
    Serial.println(9600);
    cam.config(12);
    delay(1000);
}

void loop() {
    Serial.println("Taking pic");
    cam.takePic();
    
    delay(1000);
    
    Serial.println("Taking vid");
    cam.turnOn();
    delay(5000);
    cam.turnOff();
    
    Serial.println("Wait");
    delay(10000);
}