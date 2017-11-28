#ifndef __ROLY_BODY_COMFORTABLE_ARM_H
#define __ROLY_BODY_COMFORTABLE_ARM_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "roly/body/modules/BodyModule.h"
#include "maty/math/Click.h"

namespace roly
{
// Module used to have a comfortable arm posture.
// States: 
// RELAXED: arm in comfort zone
// OUT: arm moving out of comfort zone
// TIRED: motionless arm out of comfort zone
// RELAX: command arm relax posture
// Output: 
// arm position (pan, tilt, radius)
class ComfortableArm : public BodyModule
{
public:
    // states of the module
    enum eState
    {
         eSTATE_RELAXED,           
         eSTATE_OUT, 
         eSTATE_TIRED, 
         eSTATE_RELAX 
    };
    
private:    
    static log4cxx::LoggerPtr logger;
    // bus
    bool binhibited;
    // logic
    int armPosture[3];            // measured arm posture (pan, tilt, radius)
    int armSpeed[3];              // measured arm speed (vpan, vtilt, vradius)
    bool barmMoving;    
    bool bcomfortZone;
    maty::Click oClickTired;
    // config
    int relaxPosture[3];            // arm's relax posture (pan, tilt, radius)
    float tolAngle;                   // allowed (pan, tilt) tolerance of relax posture (degrees)
    float tolRadius;                 // allowed radial tolerance of relax posture (cm)
    int maxTiredMillis;            // max allowed time for a tired arm  (motionless & out of comfort) (milliseconds)

public:
        ComfortableArm();
        //~ComfortableArm();
                               
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
        
        // sends message to arm system
        void requestComfortPosture();
        
        // check if arm is in the comfort zone (near the relax posture)
        void checkComfortZone();
        // checks if arm is moving 
        void checkArmMovement();
};
}
#endif
