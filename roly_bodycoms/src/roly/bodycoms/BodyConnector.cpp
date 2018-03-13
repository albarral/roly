/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/bodycoms/BodyConnector.h"

namespace roly
{
BodyConnector::BodyConnector()
{    
    pBodyBus = 0;
    bconnected = false;
}

void BodyConnector::connect2Bus(BodyBus& oBodyBus)
{
    pBodyBus = &oBodyBus;
    bconnected = true;
}

}