#ifndef __ROLY_BODYCORE_BODYTALK_H
#define __ROLY_BODYCORE_BODYTALK_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "talky/Talk2Target.h"

namespace roly
{
class BodyTalk
{
    private:        
        bool benabled;
        // arm talkers
        talky::Talk2Target oTalk2ArmCycler; // arm cycler category
        talky::Talk2Target oTalk2ArmAxes; // arm axes category
        
    public:
        BodyTalk();
        //~BodyTalk();
        
        void init();        
        bool isEnabled() {return benabled;};
        
        talky::Talk2Target& getTalk2ArmCycler() {return oTalk2ArmCycler;};
        talky::Talk2Target& getTalk2ArmAxes() {return oTalk2ArmAxes;};
};

}    
#endif
