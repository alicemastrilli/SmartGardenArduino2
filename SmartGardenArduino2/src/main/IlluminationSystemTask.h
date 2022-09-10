#ifndef __ILLUMINATION_SYSTEM_TASK__
#define __ILLUMINATION_SYSTEM_TASK__
#include "Arduino.h"

#include "TaskWithState.h"
#include "Led.h"
#include "LedExt.h"
#include "SmartGarden.h"
class IlluminationSystemTask: public TaskWithState{
public:
    IlluminationSystemTask(SmartGarden* pSG);
    void tick();
    long stateTimestamp;
    long elapsedTimeInState();
    void setState(int state);

    void turnOnLed(int numLed);
    void turnOffLed(int numLed);
    void setLuminosity(int numLed, int brightness);
private:
    SmartGarden* pSmartGarden;

    enum {WORKING, ALARM} state;
    Led greenLed[2];
    LedExt intensityLed[2];
};

#endif
