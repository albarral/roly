#ifndef __ROLY_BODY_COMFORTABLE_ARM_H
#define __ROLY_BODY_COMFORTABLE_ARM_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "roly/body/modules/BodyModule.h"
#include "tron2/coms/arm/ArmClient.h"

namespace roly
{
// Module used to have a comfortable arm posture.
// States: 
// STILL: motionless arm 
// MOVING: arm moving
// RELAX: command relax posture
// Output: 
// arm position (pan, tilt, radius)
class ComfortableArm : public BodyModule
{
public:
    // states of the module
    enum eState
    {
         eSTATE_STILL, 
         eSTATE_MOVING, 
         eSTATE_RELAX 
    };
    
private:    
    static log4cxx::LoggerPtr logger;
    tron2::ArmClient oArmClient;         // client for arm control
    // config
    int relaxPosture[3];            // arm's relax posture (pan, tilt, radius)
    float tolAngle;                   // allowed (pan, tilt) tolerance of relax posture (degrees)
    float tolRadius;                 // allowed radial tolerance of relax posture (cm)
    float tiredChange4Still;           // tired change for still arm (units)
    float tiredChange4Moving;      // tired change for moving arm (units)    
    // logic
    int armPosture[3];            // measured arm posture (pan, tilt, radius)
    int armSpeed[3];              // measured arm speed (vpan, vtilt, vradius)
    bool barmMoving;    
    bool bcomfortZone;
    float tired;                       // tiredness 

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
                
        // checks if arm is moving and if it's in the comfort zone (near the relax posture)
        void senseArm();
        // update tired state
        void updateTired(float change);        
        // sends message to arm system
        void requestComfortPosture();
};
}
#endif
