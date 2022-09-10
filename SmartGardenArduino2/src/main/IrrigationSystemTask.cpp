#include "IrrigationSystemTask.h"
#include "Arduino.h"
#include "servo_motor_impl.h"
#include "config.h"
#include "string.h"
#define X_SECONDS 1000
#define Y_SECONDS 4000
IrrigationSystemTask::IrrigationSystemTask(SmartGarden* pSG):pSmartGarden(pSG){
    pMotor = new ServoMotorImpl(SERVO_PIN);
    currentMakingStep = 0;
    this->open();
    setState(WORKING);
}
void IrrigationSystemTask::setSpeed(int speed){
    this->speed = speed;
}
void IrrigationSystemTask::open(){
    pMotor->on();
    pMotor->setPosition(0);
}

void IrrigationSystemTask::close(){
    pMotor->off();
}
void IrrigationSystemTask::tick(){
    switch (state){    
    case WORKING: {
        if (elapsedTimeInState() > Y_SECONDS){
            setState(PAUSE);
            pSmartGarden->setIrrigationInPause(true);
            this->close();
        }
        setSpeed(pSmartGarden->getSpeedIrrigation());
        currentMakingStep++;
        long angle = map (elapsedTimeInState(), 0, this->speed, 20, 155);
        pMotor->setPosition(angle);   
        
        break;
    }
    

    case PAUSE: {
        if (elapsedTimeInState() > X_SECONDS && pSmartGarden->getState() != 2){
            setState(WORKING);
            pSmartGarden->setIrrigationInPause(false);
            this->open();
        }
        break;
    }
    }
}
long IrrigationSystemTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}
void IrrigationSystemTask::setState(int s){
    this->state = s;
    stateTimestamp = millis();
}
