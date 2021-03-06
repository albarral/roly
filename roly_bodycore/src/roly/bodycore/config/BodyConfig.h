#ifndef __BODY_CORE_BODYCONFIG_H
#define __BODY_CORE_BODYCONFIG_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

namespace roly
{
class BodyConfig 
{
 public: 
    static const int ARTISTIC1 = 1; // artistic module 1
    static const int ARTISTIC2 = 2; // artistic module 2

private:                
        float modulesFreq;  // execution frequency for all modules (loops/sec)
        int behaviourLevels; // num of behaviour levels used to control the body
        float angleTol;         // allowed (pan, tilt) tolerance for arm positions (degrees)
        float radiusTol;        // allowed radial tolerance for arm positions (cm)
        
    public:
        BodyConfig();
        //~BodyConfig();
                        
        float getModulesFreq() {return modulesFreq;}
        float getBehaviourLevels() {return behaviourLevels;}
        
        float getAngleTolerance() {return angleTol;}; 
        float getRadialTolerance() {return radiusTol;};         
};

}

#endif
