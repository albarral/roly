#ifndef __ROLY_BODY_EXPRESSIVE_H
#define __ROLY_BODY_EXPRESSIVE_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <log4cxx/logger.h>

#include "roly/body/modules/BodyModule.h"
#include "roly/body/moves/ArmMovement.h"
#include "tron/util/Click.h"
#include "tron2/coms/arm/ArmClient.h"

namespace roly
{
// Module used to express feelings through arm movements.
// States: 
// REST: wait for action requests
// ACTION: perform arm movement step as defined in action sequence
// WAIT: wait for present step duration
// DONE: all steps of action sequence done
// Output: 
// arm position (pan, tilt, radius) or arm speed (vpan, vtilt, vradius)
class Expressive : public BodyModule
{
public:
    // actions to express
    enum eAction
    {
         eEXPRESS_JOY,
//         eEXPRESS_ANGER,
//         eEXPRESS_DENY,
//         eEXPRESS_ACCEPT,
         eEXPRESS_DIM
    };
public:
    // states of the module
    enum eState
    {
         eSTATE_REST,           
         eSTATE_ACTION, 
         eSTATE_WAIT
    };
    
private:    
    static log4cxx::LoggerPtr logger;
    // logic
    tron2::ArmClient oArmClient;     // client for arm control
    std::vector<ArmMovement> listMovements;
    int step;       // present step of arm movement sequence
    int stepDuration;  // duration of present step
    tron::Click oClickTired;

public:
        Expressive();
        //~Expressive();
                               
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
        
        // load arm movement sequence for specified action
        void loadMovement4Action(int action);
        // request arm posture or arm speed
        void performStep(ArmMovement& oArmMovement);    
        
        void loadMovement4Joy();
};
}
#endif
