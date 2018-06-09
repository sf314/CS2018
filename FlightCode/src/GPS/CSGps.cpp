// Implementatin file


#include "CSGps.h"


CSGps::CSGps(SoftwareSerial* ss) {
    serial = ss;
    satellites = 0;
    altitude = 0;
    fix = false;
    
    lat = 0;
    lon = 0;
    time = 0;
    
    hour = 0, minute = 0, seconds = 0, year = 0, month = 0, day = 0;
    
    shouldDebug = false;
}

void CSGps::update() {
    // Read character, store in string
    if (serial->available()) {
        char c = serial->read(); // Works
        // cout << "update: c = " << c << endl;
        // Append to string. 
        if (c == '$') { // Start of packet. Clear string.
            // cout << "\tupdate: start of packet" << endl;
            temp = c; // Available in arduino?
            packetReceived = false;
        } else if (c == '\r') { // End of packet. Parse. DO NOT CLEAR YET.
            // cout << "\tupdate: end of packet" << endl;
            // Do checksum?
            // cout << "Packet: " << temp << endl; // Works
            // Serial.println("GPS: Packet = " + temp);
            parsePacket();
            packetReceived = true;
        } else { // Simple append
            packetReceived = false;
            temp += c;
        }
    }
    
    // if (packetReceived) {
    //     Serial.println("Packet received!");
    //     packetReceived = false;
    // }
}

void CSGps::debugln(String s) {
    // If debug, print string to Serial
    if (shouldDebug) {
        Serial.println("CSGps: " + s);
    }
}

bool CSGps::available() {
    return serial->available();
}

char CSGps::read() {
    return serial->read();
}

void CSGps::begin(int baud) {
    serial->begin(baud);
}





// $GPGGA,033109.297,3325.2589,N,11155.7849,W,1,09,0.88,394.6,M,-26.5,M,,*55
void CSGps::parsePacket() {
    Serial.println("CSGPS.parsePacket() on temp: " + temp);
    // Break packet into components. Update vars if certain packet type
    // Use atof instead of atoi (doubles instead of ints)
    // Operate on temp string
    // vector<string> strings;
    int packetLen = 20;
    String strings[packetLen];
    int current_i = 0;
    
    String s = "";
    for (int i = 0; i < temp.length(); i++) {
        char c = temp.charAt(i);
        // cout << "parsePacket: Read " << c << endl;
        if (c == ',' || c == '\r') { // Push current string onto list
            strings[current_i] = s;
            Serial.println("\tFound: " + s);
            s = ""; // Reset current string
        } else if (c == '$') { // Don't push on the first bit
            // Skip
        } else {
            s += c; // Can push characters onto it
        }
    }
    
    // Print all detected strings
    
    // Here is where you'd choose the packet type:
    // if (strings[0] == "GPGGA") {
    if (temp.startsWith("$GPGGA")) {
        // cout << "^^This was a GPGGA packet!" << endl;
        // lat = 
        Serial.println("GPGGA found!");
        Serial.println("\tlat: " + temp.substring());
        Serial.println("\tlon: " + strings[4]);
        // lat = atof(strings[2].c_str());
        // lon = atof(strings[4].c_str());
        // time = atof(strings[1].c_str());
        // altitude = atof(strings[9].c_str());
        // lat = strings[2].toDouble();
        // lon = strings[4].toDouble();
        // time = strings[1].toDouble();
        // altitude = strings[9].toDouble();
        packetReceived = true;
    } else {
        packetReceived = false; // Ignore all other types
    }
}