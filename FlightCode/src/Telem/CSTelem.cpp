/*
CSTelem.cpp
Stephen Flores
Provide class and interface for saving telemetry 
Eliminates clutter of global variables
Should model as a singleton?
*/


#include "CSTelem.h"

CSTelem::CSTelem(int id) {
    teamID = id; 
    met = 0;
    packetCount = 0;
    altitude = 0.0;
    pressure = 0.0;
    temp = 0.0;
    voltage = 0.0;
    state = 0;
    
    gps_time = 0;
    gps_lat = 0.0;
    gps_lon = 0.0;
    gps_alt = 0.0;
    gps_sats = 0;
    
    gyro_x = 0.0;
    gyro_y = 0.0;
    gyro_z = 0.0;
}

CSTelem::CSTelem() {
    teamID = 1234; 
    met = 0;
    packetCount = 0;
    altitude = 0.0;
    pressure = 0.0;
    temp = 0.0;
    voltage = 0.0;
    state = 0;
    
    gps_time = 0;
    gps_lat = 0.0;
    gps_lon = 0.0;
    gps_alt = 0.0;
    gps_sats = 0;
    
    gyro_x = 0.0;
    gyro_y = 0.0;
    gyro_z = 0.0;
}

String CSTelem::asString() {
    // Return the telem as one single string
    String returnString = String(teamID) + ",";
    returnString += String(met) + ",";
    returnString += String(packetCount) + ",";
    returnString += String(altitude) + ",";
    returnString += String(pressure) + ",";
    returnString += String(temp) + ",";
    returnString += String(voltage) + ",";
    returnString += String(gps_time) + ",";
    returnString += String(gps_lat) + ",";
    returnString += String(gps_lon) + ",";
    returnString += String(gps_alt) + ",";
    returnString += String(gps_sats) + ",";
    returnString += String(gyro_x) + ",";
    returnString += String(gyro_y) + ",";
    returnString += String(gyro_z) + ",";
    returnString += String(state);
    return returnString;
}