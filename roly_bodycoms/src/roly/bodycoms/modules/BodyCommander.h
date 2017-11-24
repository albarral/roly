#ifndef _ROLY_BODYCOMS_BODYCOMMANDER_H
#define _ROLY_BODYCOMS_BODYCOMMANDER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "roly/bodycore/AmyTalker.h"
#include "tuly/control/module3.h"

namespace roly
{
// This module sends commands from body modules to external nodes.
// Commands are transformed to talky messages to be sent.
class BodyCommander : public tuly::Module3
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    bool benabled;
    // logic
    AmyTalker* pAmyTalker;

public:
    BodyCommander ();
    //~BodyCommander();

   void init(AmyTalker& oAmyTalker);
    bool isEnabled() {return benabled;};
                
private:
    void first();
    // executes the behaviour
    void loop ();    
};
}		
#endif
