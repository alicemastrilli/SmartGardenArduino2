#ifndef __COMMUNICATION_TASK__
#define __COMMUNICATION_TASK__
#include "Arduino.h"
#include "Task.h"
#include <string.h>
#include "SmartGarden.h"
#define ARDUINOJSON_ENABLE_ARDUINO_STRING 1
#include <ArduinoJson.h>

class CommunicationTask : public Task
{

    public:
        
        CommunicationTask(SmartGarden* pSG);
        void tick();
        void sendData();

    private:
        SmartGarden* pSmartGarden;
        bool irrigationOn;
        int stateToInt(String state);       
        String intToState(int state);
        String onToString(boolean isOn);
        bool isIntensityLedOn(int numLed); 
};

#endif
