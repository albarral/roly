#ifndef __ROLY_BODY_ARMSENSE2_H
#define __ROLY_BODY_ARMSENSE2_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "roly/body/BodyBehaviour.h"
#include "tron/util/Click.h"

namespace roly
{
// Behaviour used to sense the arm state
// Output: 
// moving state, comfort state and tired time 
class ArmSense2 : public BodyBehaviour
{
public:
    // states of the module
    enum eState
    {
         eSTATE_OK, 
         eSTATE_TIRED       // arm tired (still & out of comfort zone)
    };

private:    
    static log4cxx::LoggerPtr logger;
    // config
    int relaxPosture[3];            // arm's relax posture (pan, tilt, radius)
    float tolAngle;                   // allowed (pan, tilt) tolerance of relax posture (degrees)
    float tolRadius;                 // allowed radial tolerance of relax posture (cm)
    // logic
    int armPosture[3];            // measured arm posture (pan, tilt, radius)
    int armSpeed[3];              // measured arm speed (vpan, vtilt, vradius)
    bool barmMoving;    
    bool bcomfortZone;
    float tiredTime;                // tired time (secs)
    tron::Click oClick;

public:
        ArmSense2();
        //~ArmSense2();
                               
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
};
}
#endif
