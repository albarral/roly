#ifndef __ROLY_BODY_EXPRESSIVE_H
#define __ROLY_BODY_EXPRESSIVE_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include <log4cxx/logger.h>

#include "roly/body/modules/BodyModule.h"
#include "roly/body/moves/ArmMovement.h"
#include "amy/interface2/control/AxesClient.h"
#include "tron/util/Click.h"
// language themes
#include "tron2/language/objects/FeelingsTheme.h"

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
    int feeling;             // requested feeling
    amy::AxesClient oArmAxesClient;     // client for control of arm axes section
    std::vector<ArmMovement> listMovements;
    int step;       // present step of arm movement sequence
    int stepDuration;  // duration of present step
    tron::Click oClickStep;
    // language themes
    tron2::FeelingsTheme oFeelingsTheme; // feelings

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
        
        // analyzes requested feeling
        int analyseFeeling(std::string word);        
        // load arm movement sequence for specified action
        bool loadMovement4Action(int action);
        
        // performs a new step of the sequential movement
        bool performStep();
        // checks if present step has finished
        bool isStepFinished();
        
        // request arm posture or arm speed
        void transmitMovement(ArmMovement& oArmMovement);    
        
        void loadMovement4Joy();
};
}
#endif
