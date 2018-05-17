#ifndef __ROLY_BODY_ARMSENSE_H
#define __ROLY_BODY_ARMSENSE_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "roly/body/modules/BodyModule.h"

namespace roly
{
// Module used to sense the arm state
// Output: 
// moving state, comfort state and tired time 
class ArmSense : public BodyModule
{
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
    float periodSecs;               // module period (secs)

public:
        ArmSense();
        //~ArmSense();
                               
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
                
        // checks if arm is moving and if it's in the comfort zone (near the relax posture)
        void senseArm();
};
}
#endif
