/*
 Liam - DIY Robot Lawn Mower

 MPU-6050 Motion Sensor Library

 ======================
  Licensed under GPLv3
 ======================
*/

#include "Sens6050.h"
#include "Definition.h"


MPU6050 sensor(Wire);

boolean MS6050::initialize() {
  Wire.begin();                 // Join I2C bus
  sensor.Initialize();            // Initialize the compass
  sensor.Calibrate();
  
  current_heading = getHeading();
  tiltxz_filter = 0;
  tiltyz_filter = 0;

  return true;
}


void MS6050::updateHeading() {
  current_heading = getHeading();
}

void MS6050::setNewTargetHeading() {
  for (int i=0; i<10; i++)      // take 10 readings to get a stable value
    target_heading = getHeading();
}

int MS6050::headingVsTarget() {       // Will return angle difference between heading and target

  return  copysign(1.0,current_heading - target_heading) *
    copysign(1.0,abs(current_heading-target_heading)-180) *
    (180-abs(abs(current_heading-target_heading)-180));

}

int MS6050::getHeading() {
  return 0;
}

int MS6050::getTiltAngle() {
  sensor.Execute();
  int tiltxz = abs(sensor.GetAngAccX());
  int tiltyz = abs(sensor.GetAngAccY());

  tiltxz_filter = 0.9 * tiltxz_filter + 0.1 * tiltxz;
  tiltyz_filter = 0.9 * tiltyz_filter + 0.1 * tiltyz;

  if (tiltxz_filter > tiltyz_filter)
    return tiltxz_filter;
  else
    return tiltyz_filter;
}

int MS6050::getZAngle(){
  sensor.Execute();
  return 0;
  
}

int MS6050::getYAngle(){
  sensor.Execute();
  return (int) sensor.GetAngAccY();  
}

int MS6050::getXAngle(){
  sensor.Execute();
  return (int) sensor.GetAngAccX();
}
