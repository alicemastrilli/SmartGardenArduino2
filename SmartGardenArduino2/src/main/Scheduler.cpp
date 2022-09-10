#include "Scheduler.h"


//volatile bool timerFlag;

/*void timerHandler(void){
  timerFlag = true;
}
*/
void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
  this->timer = new Timer();
  //timerFlag = false;
  //long period = basePeriod;
  timer->setupPeriod(basePeriod);
  //Timer1.attachInterrupt(timerHandler);
  nTasks = 0;
}

bool Scheduler::addTask(Task* task){
  if (nTasks < MAX_TASKS-1){
    taskList[nTasks] = task;
    nTasks++;
    return true;
  }
  return false; 
}
  
void Scheduler::schedule(){   
  this->timer->waitForNextTick();
  for (int i = 0; i < nTasks; i++){
     if (taskList[i]->canTick()){
       taskList[i]->tick();
     }
  }
}
