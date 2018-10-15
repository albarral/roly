#ifndef __ROLY_BODY_EXPRESSIVE2_H
#define __ROLY_BODY_EXPRESSIVE2_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include <log4cxx/logger.h>

#include "roly/body/BodyBehaviour.h"
#include "amy/interface2/control/AxesClient.h"
#include "tron/util/Click.h"
#include "tron2/moves/BasicMovement.h"
#include "tron2/moves/SequentialMovement.h"
// language themes
#include "tron2/language/objects/FeelingsTheme.h"

namespace roly
{
// Behaviour used to express feelings through arm movements.
// States: 
// REST: wait for action requests
// ACTION: perform arm movement step as defined in action sequence
// WAIT: wait for present step duration
// DONE: all steps of action sequence done
// Output: 
// arm position (pan, tilt, radius) or arm speed (vpan, vtilt, vradius)
class Expressive2 : public BodyBehaviour
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
    tron2::SequentialMovement oSequentialMovement;  // associated movement
    int step;       // present step of movement sequence
    int stepDuration;  // duration of present step
    tron::Click oClickStep;
    amy::AxesClient oArmAxesClient;     // client for control of arm axes section
    // language themes
    tron2::FeelingsTheme oFeelingsTheme; // feelings

public:
        Expressive2();
        //~Expressive2();
                               
private:       
        // things to do when the behavior starts
        void start() override;
        // behavior sense phase
        void sense() override;            
        // behavior actuate phase
        void actuate() override;            
        // things to do when the behavior ends
        void end() override {};                     

        // write info (control & sensory) to bus
        void writeBus();        
        // analyzes requested feeling
        int analyseFeeling(std::string word);        
        // load movement sequence for specified action
        bool loadMovement(int action);
        
        // performs a new step of the sequential movement
        bool performStep();
        // checks if present step has finished
        bool isStepFinished();
        
        // request arm posture or arm speed
        void transmitMovement(tron2::BasicMovement& oBasicMovement);    
};
}
#endif
