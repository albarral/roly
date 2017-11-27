#ifndef __ROLY_BODYCOMS_BODYINSPECTOR_H
#define __ROLY_BODYCOMS_BODYINSPECTOR_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "roly/bodycore/AmyTalker.h"
#include "roly/bodycore/BodyBus.h"
#include "roly/bodycoms/in/ComsInBodySense.h"
#include "tuly/control/module3.h"

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
    AmyTalker* pAmyTalker;
    ComsInBodySense oComsInBodySense;     // object to transform talky sense info into bus signals

public:
    BodyInspector();
    //~BodyInspector();

    void init(BodyBus& oBodyBus, AmyTalker& oAmyTalker);
    bool isEnabled() {return benabled;};
                
private:
    virtual void first();
    // executes the behaviour
    virtual void loop();
    // check given subscriber for received messages and process them
    void checkSubscriber(nety::NetNodeSubscriber& oNetySubscriber);
};
}		
#endif
