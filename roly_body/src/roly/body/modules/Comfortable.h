#ifndef __ROLY_BODY_COMFORTABLE_H
#define __ROLY_BODY_COMFORTABLE_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "roly/body/modules/BodyModule.h"

namespace roly
{
// Module used to have a comfortable posture.
// States: 
// IN: body in comfortable posture
// OUT: body out of comfortable posture (request posture) 
// WAY: body on its way to the comfortable posture
// Output: 
// arm position (pan, tilt, radius)
class Comfortable : public BodyModule
{
public:
    // states of the module
    enum eType
    {
         eSTATE_IN,           
         eSTATE_OUT, 
         eSTATE_WAY 
    };
    
private:    
    static log4cxx::LoggerPtr logger;
    // bus
    bool binhibited;
    // logic
    int relaxPosture[3];            // arm's relax posture (pan, tilt, radius)
    int realPosture[3];              // arm's real posture (pan, tilt, radius)
    float dif[3];                      // distance to arm's relax posture
    float dif0[3];                   // previous distance to arm's relax posture
    float tolAngle;                   // allowed (pan, tilt) tolerance of relax posture (degrees)
    float tolRadius;                 // allowed radial tolerance of relax posture (cm)

public:
        Comfortable();
        //~Comfortable();
                               
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
        void talk2Arm();
        // read info from arm system
        void readFromArm();
        
        // measure distance 
        void measureDistance();
};
}
#endif
