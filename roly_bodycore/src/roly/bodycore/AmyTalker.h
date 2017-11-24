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
        nety::NetNodeClient oAxisClient;        // client for axis category
        nety::NetNodeClient oCyclerClient;      // client for cyclic category
        // subscribers for amy sensing
        nety::NetNodeSubscriber oAxisSubscriber;       // subscriber for axis category        
        
    public:
        AmyTalker();
        //~AmyTalker();
        
        void init();        
        bool isEnabled() {return benabled;};
        // clients
        nety::NetNodeClient& getAxisClient() {return oAxisClient;};
        nety::NetNodeClient& getCyclerClient() {return oCyclerClient;};
        // subscribers
        nety::NetNodeSubscriber& getAxisSubscriber() {return oAxisSubscriber;};
};

}    
#endif
