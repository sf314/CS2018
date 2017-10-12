// Test code for Ultimate GPS Using Hardware Serial
// (e.g. GPS for Leonardo, Flora or FeatherWing)
//
// This code shows how to test a passthru between USB and hardware serial
//
// Tested and works great with the Adafruit GPS FeatherWing
// ------> https://www.adafruit.com/products/3133
// or Flora GPS
// ------> https://www.adafruit.com/products/1059
// but also works with the shield, breakout
// ------> https://www.adafruit.com/products/1272
// ------> https://www.adafruit.com/products/746
// 
// Pick one up today at the Adafruit electronics shop
// and help support open source hardware & software! -ada


// what's the name of the hardware serial port?
#define GPSSerial Serial1
#include <SoftwareSerial.h>
SoftwareSerial s1(7,8);


void setup() {
  // wait for hardware serial to appear

  // make this baud rate fast enough to we aren't waiting on it
  Serial.begin(9600);
  Serial.println("Hey!");

  // 9600 baud is the default rate for the Ultimate GPS
  s1.begin(9600);
}

     
void loop() {
  if (s1.available()) {
    char c = s1.read();
    Serial.print(c);
  }
}
