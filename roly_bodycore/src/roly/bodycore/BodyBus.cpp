/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/bodycore/BodyBus.h"

namespace roly
{
// Constructor
BodyBus::BodyBus ()
{    
    benabled = false;
}

void BodyBus::init()
{
    benabled = true;
}

std::string BodyBus::toString()
{
    std::string text = "BodyBus:[CO_MOVER_TYPE: " + std::to_string(CO_MOVER_TYPE.getValue()) + "\n" +
        "CO_MOVER_ACTION: " + std::to_string(CO_MOVER_ACTION.getValue()) + "\n" +
        "CO_MOVER_TURN: " + std::to_string(CO_MOVER_TURN.getValue()) + "\n" +
        "CO_MOVER_WIDER: " + std::to_string(CO_MOVER_WIDER.getValue()) + "\n" +
        "CO_MOVER_TALLER: " + std::to_string(CO_MOVER_TALLER.getValue()) + "\n" +
        "CO_MOVER_FASTER: " + std::to_string(CO_MOVER_FASTER.getValue()) + 
          "\n";
    
    return text;
}

}
