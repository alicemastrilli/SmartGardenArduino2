#ifndef __SMART_GARDEN__
#define __SMART_GARDEN__

#include <Arduino.h>

class IntensityLamp {

public:
    IntensityLamp(int numLed);
    IntensityLamp();
    void setIntensity(int luminosity);
    int getIntensity();

private:
    int luminosity;
    int numLed;
};

class OnOffLamp{
public:
    OnOffLamp();
    OnOffLamp(int numLed);
    void switchOn();
    void switchOff();
    bool isOnLamp();
private:
    bool isOn;
    int numLed;
};
class SmartGarden {

public:
    SmartGarden();
    void setSpeedIrrigation(int speed);
    int getSpeedIrrigation();
    void setIsWorkingIrrigation(bool isWorking);
    void setState(int state);
    int getState();
    void setIrrigationInPause(bool inPause);
    bool isIrrigationInPause();
    void switchOnLed(int numLed);
    void switchOffLed(int numLed);
    bool isLedOn(int numLed);
    void setIntensityLed(int numLed, int value);
    int getIntensityLed(int numLed);
private:
    String name;
    int numProducts;
    int speedIrrigation;
    bool alarmMode;
    bool irrigationPause;
    IntensityLamp intensityLamp[2];
    OnOffLamp onOffLamp[2];
    enum {AUTO, MANUAL, ALARM} state;
};


#endif