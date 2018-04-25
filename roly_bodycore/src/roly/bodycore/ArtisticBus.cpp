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
    std::string text = "ArtisticBus:[ CO_ARTISTIC_FIGURE: " + std::to_string(CO_ARTISTIC_FIGURE.getRequested()) + " - " + std::to_string(CO_ARTISTIC_FIGURE.getValue()) + "\n" +
         "CO_ARTISTIC_FREQ: " + std::to_string(CO_ARTISTIC_FREQ.getRequested()) + " - " + std::to_string(CO_ARTISTIC_FREQ.getValue()) + "\n" +
         "CO_ARTISTIC_SIZE: " + std::to_string(CO_ARTISTIC_SIZE.getRequested()) + " - " + std::to_string(CO_ARTISTIC_SIZE.getValue()) + "\n" +
         "CO_ARTISTIC_ORIENTATION: " + std::to_string(CO_ARTISTIC_ORIENTATION.getRequested()) + " - " + std::to_string(CO_ARTISTIC_ORIENTATION.getValue()) + "\n" +
         "CO_ARTISTIC_RELFACTOR: " + std::to_string(CO_ARTISTIC_RELFACTOR.getRequested()) + " - " + std::to_string(CO_ARTISTIC_RELFACTOR.getValue()) + "\n" +
         "CO_ARTISTIC_HALT: " + std::to_string(CO_ARTISTIC_HALT.getRequested()) + "\n" +
            "\n";
    
    return text;
}

}
