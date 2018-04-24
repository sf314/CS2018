/*
CSTelem.h
Stephen Flores
Provide class and interface for saving telemetry 
Eliminates clutter of global variables
Should model as a singleton?
*/

#include <Arduino.h>

class CSTelem {
public:
    // Initializer
    CSTelem(int id);
    CSTelem();
    
    // Regular vars
        int teamID; // fixed
        long met; // sec
        long packetCount; // count
        double altitude; // metres
        double pressure; // hectopascals? 1atm = 1013hPa, or 1013mbar
        double temp; // °C
        double voltage; // V
        int state; // id
    
    // GPS vars
        long gps_time; // number, but technically fielded. atoi()'ed
        double gps_lat; // deg
        double gps_lon; // deg
        double gps_alt; // metres
        int gps_sats; // count
        
    // Gyro vars
        double gyro_x; // deg/s
        double gyro_y; // deg/s
        double gyro_z; // deg/s
    
    // Funcs
    String asString(void);
};