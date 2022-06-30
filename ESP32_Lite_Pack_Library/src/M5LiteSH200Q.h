#ifndef __M5LiteSH200Q_H__
#define __M5LiteSH200Q_H__

#include "I2C_SH200Q.h"

class M5LiteSH200Q {
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

    void setSH200Q(I2C_SH200Q *SH200Q) {
      imu = SH200Q;
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
    I2C_SH200Q *imu;
};

#endif
