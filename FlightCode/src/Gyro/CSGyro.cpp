

#include "CSGyro.h"

CSGyro::CSGyro() {
    Wire.begin();
    
    imu.calibrateMPU9250(imu.gyroBias, imu.accelBias);
    imu.initMPU9250();
    imu.initAK8963(imu.magCalibration);
}

float CSGyro::getDat() {
    // Cool, works. Lines 215 - 222 in MPU9250BasicAHRS.ino
    
    // Init stuff
    imu.readGyroData(imu.gyroCount);  // Read the x/y/z adc values 
    imu.getGres();

    // Calculate the gyro value into actual degrees per second
    // This depends on scale being set
    imu.gx = (float)imu.gyroCount[0]*imu.gRes;
    imu.gy = (float)imu.gyroCount[1]*imu.gRes;
    imu.gz = (float)imu.gyroCount[2]*imu.gRes;
    
    return imu.gx;
}