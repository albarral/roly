/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "roly/bodycore/ArtisticBus.h"

namespace roly
{
// Constructor
ArtisticBus::ArtisticBus ()
{    
}

std::string ArtisticBus::toString()
{
    std::string text = "ArtisticBus:[ CO_ARTISTIC_FIGURE: " + std::to_string(CO_ARTISTIC_FIGURE.getRequested()) + " - " + CO_ARTISTIC_FIGURE.getValue() + "\n" +
         "CO_ARTISTIC_SET: " + std::to_string(CO_ARTISTIC_SET.getRequested()) + " - " + CO_ARTISTIC_SET.getValue() + "\n" +
         "CO_ARTISTIC_TURN: " + std::to_string(CO_ARTISTIC_TURN.getRequested()) + " - " + CO_ARTISTIC_TURN.getValue() + "\n" +
         "CO_ARTISTIC_HALT: " + std::to_string(CO_ARTISTIC_HALT.getRequested()) + "\n" +
            "\n";
    
    return text;
}

}
