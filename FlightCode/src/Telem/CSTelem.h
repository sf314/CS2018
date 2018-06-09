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
        float altitude; // metres
        float pressure; // hectopascals? 1atm = 1013hPa, or 1013mbar
        float temp; // °C
        float volt_A; // V
        float volt_B; // V
        int state; // id
    
    // GPS vars
        double gps_time; // number, but technically fielded. atoi()'ed
        double gps_lat; // deg
        double gps_lon; // deg
        float gps_alt; // metres
        int gps_sats; // count
        
    // Gyro vars
        double gyro_x; // deg/s
        double gyro_y; // deg/s
        double gyro_z; // deg/s
    
    // Funcs
    String asString(void);
};