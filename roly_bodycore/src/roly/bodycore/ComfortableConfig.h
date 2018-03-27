#ifndef __BODY_CORE_COMFORTABLECONFIG_H
#define __BODY_CORE_COMFORTABLECONFIG_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

namespace roly
{
class ComfortableConfig 
{
private:                
    float angleTol;         // allowed (pan, tilt) tolerance of relax posture (degrees)
    float radiusTol;         // allowed radial tolerance of relax posture (cm)
    int tiredSensitivity4Still;              // tired sensitivity for still arm (units/second)
    int tiredSensitivity4Moving;          // tired sensitivity for moving arm (units/second)
    int relaxPosture[3];            // arm's relax posture (pan, tilt, radius)
            
    public:
        ComfortableConfig();
        //~ComfortableConfig();

    float getAngleTolerance() {return angleTol;}; 
    float getRadialTolerance() {return radiusTol;}; 
    int getTiredSensitivity4Still() {return tiredSensitivity4Still;}; 
    int getTiredSensitivity4Moving() {return tiredSensitivity4Moving;};
    int* getRelaxPosture() {return relaxPosture;};
};

}

#endif
