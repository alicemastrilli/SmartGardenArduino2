#include "IlluminationSystemTask.h"
#include "Arduino.h"
#include "Led.h"
#include "LedExt.h"
#include "LightExt.h"
#include "config.h"
#include "string.h"

LightExt* led;

IlluminationSystemTask::IlluminationSystemTask(SmartGarden* pSG):pSmartGarden(pSG){
    Led* l1 = new Led(LED_PIN1);
    greenLed[0] = *l1;
    Led* l2 = new Led(LED_PIN2);
    greenLed[1] = *l2;
    LedExt* l3 = new LedExt(LED_PIN3);
    intensityLed[0] = *l3;
    LedExt* l4 = new LedExt(LED_PIN4);
    intensityLed[1] = *l4;
    l1->switchOn();
    l2->switchOn();
    l4->switchOn();
    l3->switchOn();
   
  
    setState(WORKING);
}



void IlluminationSystemTask::turnOnLed(int numLed){
    greenLed[numLed].switchOn();
}

void IlluminationSystemTask::turnOffLed(int numLed){
    greenLed[numLed].switchOff();
}

void IlluminationSystemTask::setLuminosity(int numLed, int brightness){
    int value = map(brightness, 0, 5, 0, 255);
    intensityLed[numLed].setIntensity(100);
}


void IlluminationSystemTask::tick(){
    switch (state){    

    case WORKING: {
        if(this->pSmartGarden->getState() != 2){
            for(int i=0; i< NUM_GREEN_LED; i++){
                if(this->pSmartGarden->isLedOn(i)){
                    turnOnLed(i);
                } else{
                    turnOffLed(i);
                }
            }
            for(int i=0; i< NUM_INTENSITY_LED; i++){
                setLuminosity(i, pSmartGarden->getIntensityLed(i));

            }
        } else{
            setState(ALARM);

        }

        break;       
    }

    case ALARM: {
        if(this->pSmartGarden->getState() == 2){
            for(int i=0; i< NUM_GREEN_LED; i++){
                turnOffLed(i);
            }
            for(int i=0; i< NUM_INTENSITY_LED; i++){
                setLuminosity(i,0);
            }
        } else{
            setState(WORKING);
        }
        break;
    }
    }
}
long IlluminationSystemTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}
void IlluminationSystemTask::setState(int s){
    this->state = s;
    stateTimestamp = millis();
}
