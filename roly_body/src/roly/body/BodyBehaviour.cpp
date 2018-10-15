/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/body/BodyBehaviour.h"

namespace roly
{
// Constructor 
BodyBehaviour::BodyBehaviour(std::string name) : tron::Behaviour(name)
{    
    benabled = false;
    pBodyBus = 0;
 }

void BodyBehaviour::connect(BodyBus& oBodyBus)
{
    pBodyBus = &oBodyBus;    
    benabled = true;    
}

}