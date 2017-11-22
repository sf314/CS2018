// Stephen Flores
// Test driver for camera

#include <SoftwareSerial.h>
#include "Adafruit_VC0706.h"

SoftwareSerial cameraConnection(0, 1);
Adafruit_VC0706 camera = Adafruit_VC0706(&cameraConnection);

// *** SD Car stuff
#define chipSelect 10


void setup() {
    Serial.begin(9600);
    delay(1000);
    Serial.println("Testing camera");
    
    pinMode(chipSelect, OUTPUT);
    
    if (camera.begin()) {
        Serial.println("Camera initialized");
    } else {
        Serial.println("Camera not initialized");
    }
    
    delay(1000);
    Serial.println("Camera version test:");
    char* reply = camera.getVersion();
    if (reply == 0) {
        Serial.println("Failed to get reply");
    } else {
        Serial.print(reply);
    }
}

void loop() {
    // Take a pic every 5 seconds
    bool result = camera.takePicture();
    if (result) {
        Serial.println("Took a pic!");
    } else {
        Serial.println("Couldn't take a pic!");
    }
    
    delay(5000);
}