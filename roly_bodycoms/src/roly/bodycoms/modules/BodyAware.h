#ifndef __ROLY_BODYCOMS_BODYAWARE_H
#define __ROLY_BODYCOMS_BODYAWARE_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "roly/bodycore/BodyBus.h"
#include "tron/control/module3.h"
#include "amy/interface/ArmListener.h"

namespace roly
{
// This module is aware of broadcasted info from other robotic nodes.
class BodyAware : public tron::Module3
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    bool benabled;
    // logic
    BodyBus* pBodyBus;      // access to body bus
    amy::ArmListener oArmListener;

public:
    BodyAware();
    //~BodyAware();

    void init(BodyBus& oBodyBus);
    bool isEnabled() {return benabled;};
                
private:
    virtual void first();
    // executes the behaviour
    virtual void loop();
};
}		
#endif
