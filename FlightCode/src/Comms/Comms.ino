// CSComms


#include <SoftwareSerial.h>
#include "CSComms.h"

SoftwareSerial ssXbee(0, 1); // (MISO, MOSI)
CSComms xbee(&ssXbee);

void setup() {
    Serial.begin(9600);
    xbee.config();
    xbee.begin(9600);
}

int counter = 0;
void loop() {
    xbee.println("Hello: " + String(counter));
    counter++;
    delay(1000);
}