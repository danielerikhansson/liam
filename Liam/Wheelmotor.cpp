/*
 Liam - DIY Robot Lawn Mower

 Wheel Motor Library

 ======================
  Licensed under GPLv3
 ======================
*/

#include "Wheelmotor.h"


WHEELMOTOR::WHEELMOTOR(int pwmpin_, int dirpin_, int loadpin_, int smoothness) {
  pwmpin = pwmpin_;
  dirpin = dirpin_;
  loadpin = loadpin_;
  smoothness_delay = smoothness;
}




int WHEELMOTOR::setSpeedOverTime(int targetSpeed, int actionTime) {
		unsigned long _now = millis();
		if (targetSpeed != ot_currentTargetValue) {
			ot_currentTargetValue = targetSpeed;
			ot_startingValue = ot_currentValue;
			ot_setTime = _now;
		}

    int newValue;

		if (targetSpeed == ot_currentValue) {
      _atTargetSpeed = true;
      return 0;
    } else if (actionTime == 0) {
      newValue = targetSpeed;
    } else if (ot_setTime + actionTime < _now) {
      //Serial.println("Overdue");
      newValue = targetSpeed;
    } else {
      newValue = map(_now, ot_setTime, ot_setTime + actionTime, ot_startingValue, targetSpeed);
    }

		analogWrite(pwmpin, 2.55*abs(newValue));
		digitalWrite(dirpin, (newValue > 0));

		ot_currentValue = newValue;
    bool r = targetSpeed - newValue;
    _atTargetSpeed = r == 0;
    return r;
}

bool WHEELMOTOR::isAtTargetSpeed() {
  return _atTargetSpeed;;
}

void WHEELMOTOR::setSpeed(int setspeed) {
	if (setspeed > 100) setspeed = 100;
	if (setspeed < -100) setspeed = -100;

  while (setSpeedOverTime(setspeed, smoothness_delay * setspeed / 1000) != 0) {
    delay(1);
  }
}


int WHEELMOTOR::getSpeed() {
  return ot_currentValue;
}


int WHEELMOTOR::getLoad() {
  int load = 0;

  for (int i = 0; i < MOTOR_LOAD_READINGS; i++) {
    load += analogRead(loadpin);
    delay(1);
  }

  return load/MOTOR_LOAD_READINGS;
}


bool WHEELMOTOR::isOverloaded() {
  return (getLoad() > overload_level);
}

void WHEELMOTOR::setOverloadLevel(int level) {
  overload_level = level;
}

void WHEELMOTOR::setSmoothness(int level) {
  smoothness_delay = level;
}
