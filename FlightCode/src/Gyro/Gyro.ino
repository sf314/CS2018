

#include "CSGyro.h"
CSGyro gyro;

void setup() {
    Serial.begin(9600);
    
    gyro = CSGyro();
}

void loop() {
    Serial.println(gyro.getDat());
    delay(1000);
}