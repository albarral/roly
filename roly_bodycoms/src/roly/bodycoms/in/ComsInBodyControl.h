#ifndef __ROLY_BODYCOMS_IN_BODYCONTROL_H
#define __ROLY_BODYCOMS_IN_BODYCONTROL_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "roly/bodycore/BodyBus.h"
#include "talky/coms/Command.h"
#include "tuly/utils/IntegerQueue.h"

namespace roly
{
// Class used to process body control requests.
// Requests are converted to proper body bus signals
class ComsInBodyControl 
{    
public:
    // special actions
    enum eAction
    {
         eACTION_BODY_END,            // end amy process
         eACTION_DIM
    };

private:
    static log4cxx::LoggerPtr logger;            
    BodyBus* pBodyBus;      // access to arm bus
    tuly::IntegerQueue oQueueSpecialActions;  // queue of special actions
    
public:
    ComsInBodyControl();
    //~ComsArmControl();
    
    void connect2Bus(BodyBus& oBodyBus);

   // transforms command into proper call to arm interface
    bool processCommand(talky::Command& oCommand);
    
    tuly::IntegerQueue& getQueueSpecialActions() {return oQueueSpecialActions;}
    
private:
    // process commands of expressive category
    bool processExpressiveCommand(talky::Command& oCommand);
    // process commands of arm mover category
    bool processArtisticCommand(talky::Command& oCommand);
    // process command of extra category
    bool processExtraCommand(talky::Command& oCommand);

    // dummy method for to do commands
    void toDoCommand(float value);
};
}
#endif
