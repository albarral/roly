#ifndef __ROLY_BODY_ARMMOVER_H
#define __ROLY_BODY_ARMMOVER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "roly/body/modules/BodyModule.h"
//#include "roly/body/moves/MoveFactory.h"
#include "tron/talky2/arm/ArmClient.h"
#include "maty/moves/CyclicMovement.h"
#include "maty/moves/CircularMovement.h"
#include "maty/moves/WaveMovement.h"

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
    // logic
    tron::ArmClient oArmClient;     // client for arm control
    int figure;       // figure id (eFigure)
    float freq;         // frequency of cyclic movement
    float size;         // size of cyclic movement (degrees/s)
    float relFactor;   // relative xy factor of cyclic movement
    float orientation;    // orientation of cyclic movement (degrees)
    bool bcontinuous;       // continuous or simple mode
    maty::CircularMovement oCircularMovement;
    maty::WaveMovement oWaveMovement;
    maty::CyclicMovement* pActiveCyclicMovement;

public:
        Artistic();
        //~Artistic();
                               
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
        
        bool generateMovement();

        // checks if ordered movement is finished (just for simple mode)
        bool checkMovementFinished();
};
}
#endif