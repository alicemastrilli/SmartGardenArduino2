#include "Arduino.h"
#include "config.h"
#include "Scheduler.h"
#include "IrrigationSystemTask.h"
#include "SmartGarden.h"
#include "IlluminationSystemTask.h"
#include "CommunicationTask.h"
Scheduler sched;
SmartGarden* pSmartGarden;
String messaggio;
void setup() {
  Serial.begin(9600);
  Serial.flush();
  sched.init(50);

  pSmartGarden = new SmartGarden();
  Task* pIrrigationSystem = new IrrigationSystemTask(pSmartGarden);
  Task* pIlluminationSystem = new IlluminationSystemTask(pSmartGarden);
  Task* pCommunication = new CommunicationTask(pSmartGarden);
  pIrrigationSystem->init(50);
  pIlluminationSystem->init(50);
  pCommunication->init(100);
  
  sched.addTask(pIrrigationSystem);
  sched.addTask(pIlluminationSystem);
  sched.addTask(pCommunication);
}

void loop() {
  sched.schedule();
}
