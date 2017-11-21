#ifndef __ROLY_BODY_ARMMOVER_H
#define __ROLY_BODY_ARMMOVER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "roly/body/modules/BodyModule.h"
#include "roly/body/moves/CyclicMove.h"
#include "roly/body/moves/MoveFactory.h"
#include "tuly/utils/IntegerQueue.h"

namespace roly
{
// Module to perform complex cyclic movements with the arm. It controls a cycler module.
// States: 
// The module is usually in WAIT state.
// It goes to TALK state for sending commands to the cycler.
// Then returns fast to WAIT state.
// Messages:
// It sends 3 types of messages to the cycler: trigger, stop & update.
class ArmMover : public BodyModule
{
public:
    // states of ArmMover module
    enum eType
    {
         eSTATE_WAIT,           // just senses bus
         eSTATE_TALK           // send commands to cycler
    };
private:    
    // types of command
    enum eCmd
    {
         eCMD_TRIGGER,       // starts a cyclic movement   
         eCMD_STOP,           // ends a cyclic movement   
         eCMD_UPDATE       // modifies a cyclic movement
    };

    static log4cxx::LoggerPtr logger;
    // logic
    MoveFactory oMoveFactory;    
    CyclicMove oCyclicMove;    
    tuly::IntegerQueue oCommandsQueue;

public:
        ArmMover();
        //~ArmMover();
                               
private:       
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        // read bus data
        virtual void senseBus();
        // write info (control & sensory) to bus
        virtual void writeBus();
        // show module initialization in logs
        virtual void showInitialized();
        // shows the present state name
        void showState();
        
        // sends message to cyclers
        void talk2Cyclers();
        // triggers a cyclic movement
        void triggerMove();
        // stop a cyclic movement
        void stopMove();
        // changes a cyclic movement        
        void updateMove();
};
}
#endif
