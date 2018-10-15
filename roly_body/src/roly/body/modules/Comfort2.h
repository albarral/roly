#ifndef __ROLY_BODY_COMFORT2_H
#define __ROLY_BODY_COMFORT2_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "roly/body/BodyBehaviour.h"
#include "amy/interface2/control/AxesClient.h"

namespace roly
{
// Behaviour used to have a comfortable arm posture.
// States: 
// STILL: motionless arm 
// MOVING: arm moving
// RELAX: command relax posture
// Output: 
// arm position (pan, tilt, radius)
class Comfort2 : public BodyBehaviour
{
public:
    // states of the module
    enum eState
    {
         eSTATE_SENSE, 
         eSTATE_RELAX, 
         eSTATE_WAIT 
    };
    
private:    
    static log4cxx::LoggerPtr logger;
    amy::AxesClient oArmAxesClient;          // client for control of arm axes section
    // config
    int relaxPosture[3];            // arm's relax posture (pan, tilt, radius)
    float maxTiredTime;           // max allowed tired time (secs)
    // logic
    bool barmMoving;                // arm moving state
    bool bcomfortZone;             // arm comfort state 
    float tiredTime;                 // measured tired time (secs)
    int waitCycles; 

public:
        Comfort2();
        //~Comfort2();
                               
private:       
        // things to do when the behavior starts
        void start() override;
        // behavior sense phase
        void sense() override;            
        // behavior actuate phase
        void actuate() override;            
        // things to do when the behavior ends
        void end() override {};                     

        // sends message to arm system
        void requestComfort2Posture();
};
}
#endif
