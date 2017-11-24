#ifndef __ROLY_BODYCOMS_BODYLISTENER_H
#define __ROLY_BODYCOMS_BODYLISTENER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "roly/bodycore/AmyTalker.h"
#include "tuly/control/module3.h"
//#include "amy/coms/in/ComsArmControl.h"

namespace roly
{
// This module inspects broadcasted info from external processes to sense their state.
// It uses nety subscriber nodes for communication.
class BodyInspector : public tuly::Module3
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    bool benabled;
    // logic
//    ComsArmControl oComsArmControl;         // object that gets talky commands and transforms them to bus sensorl values
//    bool brequestedBodyEnd;
    AmyTalker* pAmyTalker;

public:
    BodyInspector();
    //~BodyInspector();

 //   void init(ArmBus& oArmBus);       
    void init(AmyTalker& oAmyTalker);
    bool isEnabled() {return benabled;};
        
    // check special actions
//    bool checkSpecialActions();    
//    bool getBodyEndRequested() {return brequestedBodyEnd;};
        
private:
    virtual void first();
    // executes the behaviour
    virtual void loop();
    // check given subscriber for received messages and process them
    void checkSubscriber(nety::NetNodeSubscriber& oNetySubscriber);
};
}		
#endif
