#ifndef __ROLY_BODYCOMS_BODYCONNECTOR_H
#define __ROLY_BODYCOMS_BODYCONNECTOR_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/bodycore/BodyBus.h"

namespace roly
{
// Base class used to connect to body bus.
class BodyConnector 
{    
protected:
    BodyBus* pBodyBus;      // access to body bus
    bool bconnected;
    
public:
    BodyConnector();
    //~BodyConnector();
    
    virtual void connect2Bus(BodyBus& oBodyBus);
    bool isConnected() {return bconnected;};
};
}
#endif
