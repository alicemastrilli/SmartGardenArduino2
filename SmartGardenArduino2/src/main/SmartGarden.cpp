#include "SmartGarden.h"
#include "config.h"

IntensityLamp::IntensityLamp(int numLed){
    this->numLed = numLed;
}
IntensityLamp::IntensityLamp(){}
void IntensityLamp::setIntensity(int luminosity){
    this->luminosity = luminosity;
}
int IntensityLamp::getIntensity(){
    return this->luminosity;
}
OnOffLamp::OnOffLamp(int numLed){
    this->numLed = numLed;
}
OnOffLamp::OnOffLamp(){}
void OnOffLamp::switchOn(){
    this->isOn = true;
}

void OnOffLamp::switchOff(){
    this->isOn = false;
}
bool OnOffLamp::isOnLamp(){
    return this->isOn;
}
SmartGarden::SmartGarden(){
    this->state = AUTO;
    this->speedIrrigation = 0;
    intensityLamp[0] = IntensityLamp(0);
    intensityLamp[1] = IntensityLamp(1);
    onOffLamp[0] = OnOffLamp(0);
    onOffLamp[1] = OnOffLamp(1);
    onOffLamp[0].switchOff();
    onOffLamp[1].switchOff();
    setIntensityLed(1,  0);
    setIntensityLed(0,  0);
    
}


void SmartGarden::setSpeedIrrigation(int speed){
    this->speedIrrigation = speed;
}
int SmartGarden::getSpeedIrrigation(){
    return this->speedIrrigation;
}

void SmartGarden::setIrrigationInPause(bool inPause){
    this->irrigationPause = inPause;
}

bool SmartGarden::isIrrigationInPause(){
    return this->irrigationPause;
}

void SmartGarden::setState(int s){
    this->state = s;
}
int SmartGarden::getState(){
    return this->state;
}
void SmartGarden::switchOnLed(int numLed){
    this->onOffLamp[numLed].switchOn();
}
void SmartGarden::switchOffLed(int numLed){
    this->onOffLamp[numLed].switchOff();
}
bool SmartGarden::isLedOn(int numLed){
    return this->onOffLamp[numLed].isOnLamp();
}
void SmartGarden::setIntensityLed(int numLed, int value){
    this->intensityLamp[numLed].setIntensity(value);
}
int SmartGarden::getIntensityLed(int numLed){
 // Serial.println(this->intensityLamp[numLed].getIntensity());
    return this->intensityLamp[numLed].getIntensity();
}
