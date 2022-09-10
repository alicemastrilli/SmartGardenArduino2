#include "CommunicationTask.h"
#include "config.h"
#include "Arduino.h"
#include "String.h"
#include "MsgServiceBT.h"
#include <SoftwareSerial.h>

/* 
*   Stato: ST-IRR-
*   Temperatura: TM-
*   Photoresistor: PH- 
*/
String msg;
MsgServiceBT msgServiceBT(RX_PIN, TX_PIN);
CommunicationTask::CommunicationTask(SmartGarden* pSG):pSmartGarden(pSG){
  msgServiceBT.init();  

  //Serial.flush();
}

void CommunicationTask::sendData(){
    StaticJsonDocument<1150> doc;
    JsonObject root = doc.to<JsonObject>();

    root["s"] = pSmartGarden->getState();

    JsonArray array = root.createNestedArray("a");
    JsonObject a1 = array.createNestedObject();
    a1["s"]= pSmartGarden->isLedOn(0);
    a1["n"] = "Lamp 1";

    JsonObject a2 = array.createNestedObject();
    a2["s"]= pSmartGarden->isLedOn(1);
    a2["n"] = "Lamp 2";

    JsonArray b = root.createNestedArray("b");
    JsonObject b1 = b.createNestedObject();
    b1["s"]= isIntensityLedOn(0);
    b1["n"] = "Lamp 3";
    b1["i"] = 3;
    b1["x"] = 4;
    b1["y"] = 0;
    JsonObject b2 = b.createNestedObject();
    b2["s"]= pSmartGarden->isLedOn(1);
    b2["n"] = "Lamp 4";
    b2["i"] = 6;
    b2["x"] = 4;
    b2["y"] = 0;
    JsonObject c = root.createNestedObject("c");
    c["s"]= pSmartGarden->isIrrigationInPause();
    c["n"] = "I";
    c["i"] = pSmartGarden->getSpeedIrrigation();
    c["x"] = 10;
    c["y"] = 0;


   
    serializeJson(doc, Serial);
}
void CommunicationTask::tick(){
  //manda i dati in formato json (i valori dei vari componenti)
  sendData();
  if(Serial.available() ){
      msg = Serial.readStringUntil('\n');
      DynamicJsonDocument info(1064);
      DeserializationError error = deserializeJson(info, msg );
      if (error) {          
        Serial.println(error.f_str());
        return;
      } else {
        for(int i=0; i<NUM_GREEN_LED; i++){
            if(info["a"][i]["state"] == 1){
                pSmartGarden->switchOnLed(i);    
            } else {
                pSmartGarden->switchOffLed(i);
            }
        }
        for(int i=0; i<NUM_INTENSITY_LED; i++){
            pSmartGarden->setIntensityLed(i, info["intensityValues"][i]["intensity"]);
        }
        pSmartGarden->setSpeedIrrigation(info["motor"]["intensity"]);
        String state = info["state"];
        pSmartGarden->setState(stateToInt(state));
    }
    }
}

    
bool CommunicationTask::isIntensityLedOn(int numLed){
    return pSmartGarden->getIntensityLed(numLed) != 0;
}
String CommunicationTask::onToString(boolean isOn){
    if(isOn){
        return "ON";
    }
    return "OFF";
}
int CommunicationTask::stateToInt(String state){
    if(state =="AUTO"){
        return 0;
    } else if(state== "MANUAL"){
        return 1;
    }
    return 2;
}
String CommunicationTask::intToState(int state){
    if(state == 0){
        return "AUTO";
    } else if(state==1){
        return "MANUAL";
    } return "ALARM";
}
