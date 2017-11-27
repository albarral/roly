#ifndef __ROLY_BODYCORE_AMYTALKER_H
#define __ROLY_BODYCORE_AMYTALKER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "nety/NetNodeClient.h"
#include "nety/NetNodeSubscriber.h"

namespace roly
{
// Class with all nety nodes needed for communication with amy process
class AmyTalker
{
    private:        
        bool benabled;
        // clients for amy control
        nety::NetNodeClient oArmAxisClient;        // client for arm axis category
        nety::NetNodeClient oArmCyclerClient;      // client for arm cyclic category
        // subscribers for amy sensing
        nety::NetNodeSubscriber oArmAxisSubscriber;       // subscriber for arm axis category        
        
    public:
        AmyTalker();
        //~AmyTalker();
        
        void init();        
        bool isEnabled() {return benabled;};
        // clients
        nety::NetNodeClient& getArmAxisClient() {return oArmAxisClient;};
        nety::NetNodeClient& getArmCyclerClient() {return oArmCyclerClient;};
        // subscribers
        nety::NetNodeSubscriber& getArmAxisSubscriber() {return oArmAxisSubscriber;};
};

}    
#endif
