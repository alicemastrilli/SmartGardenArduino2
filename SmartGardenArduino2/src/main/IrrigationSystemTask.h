#ifndef __IRRIGATION_SYSTEM_TASK__
#define __IRRIGATION_SYSTEM_TASK__
#include "Arduino.h"
#include "SmartGarden.h"
#include "Task.h"
#include "servo_motor.h"

class IrrigationSystemTask: public Task {

public:
  IrrigationSystemTask(SmartGarden* pSG); 
  void tick();
private:  
  int currentMakingStep;
  int speed;
  void setState(int state);
  long elapsedTimeInState();
  void setSpeed(int speed);
  void close();
  void open();
  enum {WORKING, PAUSE} state;
  long stateTimestamp;
  SmartGarden* pSmartGarden;
  ServoMotor* pMotor;
};

#endif
