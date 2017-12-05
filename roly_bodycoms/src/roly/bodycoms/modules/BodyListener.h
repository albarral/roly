#ifndef __ROLY_BODYCOMS_BODYLISTENER_H
#define __ROLY_BODYCOMS_BODYLISTENER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "roly/bodycore/BodyBus.h"
#include "roly/bodycoms/in/ComsInBodyControl.h"
#include "nety/NetNodeServer.h"
#include "tuly/control/module3.h"

namespace roly
{
// This module listens to external control requests for body control and processes them.
// It uses nety server nodes for communications.
class BodyListener : public tuly::Module3
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    bool benabled;
    // logic
    nety::NetNodeServer oBodyServer4Expressive;      // server for expressive category
    nety::NetNodeServer oBodyServer4Artistic;      // server for arm mover category
    nety::NetNodeServer oBodyServer4Extra;             // server for extra category
    ComsInBodyControl oComsInBodyControl;         // object that gets talky commands and transforms them to bus control values
    bool brequestedBodyEnd;

public:
    BodyListener();
    //~BodyListener();

    void init(BodyBus& oBodyBus);       
    bool isEnabled() {return benabled;};
        
    bool checkSpecialActions();
    bool getBodyEndRequested() {return brequestedBodyEnd;};
        
private:
    virtual void first();
    // executes the behaviour
    virtual void loop();
    // check given server for received messages and process them
    void checkServer(nety::NetNodeServer& oNetyServer);
};
}		
#endif
