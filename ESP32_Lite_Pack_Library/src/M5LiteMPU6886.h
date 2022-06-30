#ifndef __M5LiteMPU6886_H__
#define __M5LiteMPU6886_H__

#include "I2C_MPU6886.h"

class M5LiteMPU6886 {
  public:
    enum Ascale {
      AFS_2G = 0,
      AFS_4G,
      AFS_8G,
      AFS_16G
    };

    enum Gscale {
      GFS_250DPS = 0,
      GFS_500DPS,
      GFS_1000DPS,
      GFS_2000DPS
    };

    void setMPU6886(I2C_MPU6886 *mpu6886) {
      imu = mpu6886;
    }

    int Init(void) {
      return imu->begin();
    }

    void getAccelData(float* ax, float* ay, float* az) {
      imu->getAccel(ax, ay, az);
    }

    void getGyroData(float* gx, float* gy, float* gz) {
      imu->getGyro(gx, gy, gz);
    }

    void getTempData(float *t) {
      imu->getTemp(t);
    }

  private:
    I2C_MPU6886 *imu;
};

#endif
