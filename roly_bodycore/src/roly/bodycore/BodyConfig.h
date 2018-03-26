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
    private:                
        float modulesFreq;  // execution frequency for all modules (loops/sec)
        
    public:
        BodyConfig();
        //~BodyConfig();
                        
        void setModulesFreq(float value) {modulesFreq = value;}
        float getModulesFreq() {return modulesFreq;}
};

}

#endif
