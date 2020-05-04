/*
 Liam - DIY Robot Lawn Mower

 MPU-6050 Motion Sensor Library

 ======================
  Licensed under GPLv3
 ======================
*/

#ifndef _MS6050_H_
#define _MS6050_H_

#include "MotionSensor.h"
#include <Wire.h>
//#include <I2Cdev.h>
#include <TinyMPU6050.h>

class MS6050 : public MOTIONSENSOR{
  public:
    virtual boolean initialize();
    virtual void updateHeading();
    virtual int getHeading();
    virtual void setNewTargetHeading();
    virtual int headingVsTarget();
    virtual int getTiltAngle();
    virtual int getXAngle();
    virtual int getYAngle();
    virtual int getZAngle();
};

#endif /* _MS6050_H_ */
