#ifndef __ROLY_BODY_COMFORT_H
#define __ROLY_BODY_COMFORT_H

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
class Comfort : public BodyModule
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
    tron2::ArmClient oArmClient;         // client for arm control
    // config
    int relaxPosture[3];            // arm's relax posture (pan, tilt, radius)
    float maxTiredTime;           // max allowed tired time (secs)
    // logic
    bool barmMoving;                // arm moving state
    bool bcomfortZone;             // arm comfort state 
    float tiredTime;                 // measured tired time (secs)

public:
        Comfort();
        //~Comfort();
                               
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
};
}
#endif
