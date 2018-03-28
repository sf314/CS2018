
#ifndef _csgyro_h
#define _csgyro_h

// extern "C"
// {
//   #include "avr_i2c.h"
// }

// #include "mpu9250.h"
// #include "SparkFunIMU.h"
#include "MPU9250.h"

class CSGyro {
public:
    // Init
    CSGyro();
    
    // Vars
    
    // Funcs
    float getDat();
    
private:
    // MPU_9250 myIMU;
    MPU9250 imu;
};


#endif