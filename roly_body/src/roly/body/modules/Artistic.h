#ifndef __ROLY_BODY_ARMMOVER_H
#define __ROLY_BODY_ARMMOVER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "roly/bodycore/ArtisticBus.h"
#include "roly/body/modules/BodyModule.h"
#include "tron2/moves/CyclicMovement.h"
#include "tron2/moves/MoveFactory.h"
#include "tron/math/CyclicComponent.h"
#include "amy/interface/ArmClient.h"

namespace roly
{
// Module to perform complex cyclic movements with the arm. It controls the frontal cycler module of amy node.
// Messages:
// It sends 3 types of messages to the cycler: trigger, stop & update.
class Artistic : public BodyModule
{
public:
    // states of Artistic module
    enum eType
    {
         eSTATE_IDLE,           // waits for requests
         eSTATE_LAUNCH,      // launches cycler movement
         eSTATE_WAIT,           // waits for movement to finish (until halt request in continuous mode)
         eSTATE_UPDATE,      // updates cycler movement
         eSTATE_STOP           // stops cycler movement
    };

private:    
    static log4cxx::LoggerPtr logger;
    int id;                                // id of artistic module (defines the target cycler)
    // bus        
    ArtisticBus* pArtisticBus;  // bus connection for this module
    // logic
    amy::ArmClient oArmClient;     // client for arm control
    bool bcontinuous;       // continuous or simple mode
    tron2::MoveFactory oMoveFactory; // utility class for movements creation
    tron2::CyclicMovement oCyclicMovement;
    int figure;         // requested figure for cycler

public:
        Artistic();
        //~Artistic();
                               
        void setID(int value);
        int getID() {return id;};
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
        
        // triggers a cyclic movement
        void triggerMove();
        // stop a cyclic movement
        void stopMove();
        // changes a cyclic movement        
        void updateMove();
        
        int translateFigure2Movement(int value);
        
        // updates cyclic component of cycler (main or secondary)
        void updateCyclerComponent(bool bmain, tron::CyclicComponent& oCyclicComponent);
        // stop cyclic component of cycler (main or secondary)
        void stopCyclerComponent(bool bmain);

        // checks if ordered movement is finished (just for simple mode)
        bool checkMovementFinished();
};
}
#endif
