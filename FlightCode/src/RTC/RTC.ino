// Testing software-enabled RTC. Super weird...
// Initializes using the time that the code was compiled/deployed
// by using the __DATE__ and __TIME__ macros. From there, it
// simply calculates delta time. However, it also provides
// means of switching between UNIX time and readable time, which
// will be useful when combined with GPS. 

#include <Arduino.h>
#include <Wire.h>
#include "RTClib.h"

RTC_Millis rtc;
DateTime bootTime;

void setup() {
    Serial.begin(9600);
    
    rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
    bootTime = rtc.now();
}

long currentTime = 0;
long previousTime = 0;

void loop() {
    currentTime = millis();
    
    if (currentTime - previousTime >= 1000) {
        DateTime now = rtc.now();
        
        Serial.println("MET");
        Serial.println(now.unixtime() - bootTime.unixtime());
        
        previousTime = currentTime;
    }
}