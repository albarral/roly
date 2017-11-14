/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/body/modules/BodyModule.h"

namespace roly
{
// Constructor 
BodyModule::BodyModule()
{    
    modName = "BodyModule";
    benabled = false;
    bconnected = false;
    pBodyBus = 0;
    pBodyTalk = 0;
 }

void BodyModule::init()
{
    benabled = true;    
    showInitialized();
}

void BodyModule::connect(BodyBus& oBodyBus, BodyTalk& oBodyTalk)
{
    pBodyBus = &oBodyBus;    
    pBodyTalk = &oBodyTalk;
    bconnected = true;
}

}