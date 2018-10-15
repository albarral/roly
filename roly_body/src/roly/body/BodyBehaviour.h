#ifndef __ROLY_BODY_BODYBEHAVIOUR_H
#define __ROLY_BODY_BODYBEHAVIOUR_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron/control/Behaviour.h"
#include "roly/bodycore/BodyBus.h"

namespace roly
{
// Base class for body behaviours
// Must be connected to body bus in order to enable it.
class BodyBehaviour : public tron::Behaviour
{
protected:
    bool benabled;
    BodyBus* pBodyBus;     // access to body bus

public:
    BodyBehaviour(std::string name);
    //~BodyBehaviour();

    // bus connection 
    void connect(BodyBus& oBodyBus);
    bool isEnabled() {return benabled;};    
};
}		
#endif
