#ifndef __ROLY_BODY_BODYMODULE_H
#define __ROLY_BODY_BODYMODULE_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tuly/control/module3.h"
#include "roly/bodycore/BodyBus.h"

namespace roly
{
// Base class for arm modules.
// Usage:
// - connect bus
// - init
// - on (now it works)
// - off    
class BodyModule : public tuly::Module3
{
protected:
    bool benabled;
    // bus
    bool bconnected;        // connected to bus
    bool binhibited;
    BodyBus* pBodyBus;     // access to body bus

public:
    BodyModule();
    //~BodyModule();

    // initialize module
    void init();
    bool isEnabled() {return benabled;};

    // bus connection 
    void connect(BodyBus& oBodyBus);
    bool isConnected() {return bconnected;};
    
protected:
    // read bus data   
    virtual void senseBus() = 0;
    // write action commands or sensor info to bus    
    virtual void writeBus() = 0;
    // show module initialization in logs
    virtual void showInitialized() = 0;

};
}		
#endif
