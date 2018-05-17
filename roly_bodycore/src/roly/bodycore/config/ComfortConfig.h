#ifndef __BODY_CORE_COMFORTABLECONFIG_H
#define __BODY_CORE_COMFORTABLECONFIG_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

namespace roly
{
class ComfortConfig 
{
private:                
    float tiredTime4Relax;         // tired time (secs) allowed until relax is requested
    int relaxPosture[3];            // arm's default relax posture (pan, tilt, radius)
            
    public:
        ComfortConfig();
        //~ComfortConfig();

    float getTiredTime4Relax() {return tiredTime4Relax;}; 
    int* getRelaxPosture() {return relaxPosture;};
};

}

#endif
